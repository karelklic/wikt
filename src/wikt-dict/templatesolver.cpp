/* This file is part of Wikt.
 *
 * Wikt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Wikt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Wikt. If not, see <http://www.gnu.org/licenses/>.
 */
/* This file is required by commandPrepToMid. */
#include "templatesolver.h"
#include "namespaceurlfunctions.h"
#include "templateutils.h"
#include "parserfunctions.h"
#include "formattingfunctions.h"
#include "pagenamefunctions.h"
#include "parameterlist.h"
#include "format2reader.h"
#include <libwikt/debug.h>
#include <libwikt/namespace.h>
#include <QRegExp>
#include <QTextStream>

#define PIPE_ESCAPE "1P#-"
#define LEFT_BRACE_ESCAPE "1L#-"
#define EQUALS_ESCAPE "1E#0-"
#define RIGHT_BRACE_ESCAPE "1R#-"

static void
evaluateTemplate(QString &wikiText,
                 int from,
                 int to,
                 const QString &pageName,
                 bool &pageNameUsed,
                 QMap<QString, QString> &entryCache,
                 Format2Reader &reader,
                 bool updateTemplateUsage,
                 bool debug);

static QString
evaluateTemplate(const QString &templateText,
                 const QString &pageName,
                 bool &pageNameUsed,
                 QMap<QString, QString> &entryCache,
                 Format2Reader &reader,
                 bool updateTemplateUsage,
                 bool debug);


/// We measure which templates are used in debug mode.
static QMap<QString, int>
templateUsage;

/// Template cache across entries.
QMap<QString, QString>
crossEntryCache;

QList<QPair<int, QString> >
templateUsageList()
{
  QList<QPair<int, QString> > usageList;
  for (QMap<QString, int>::const_iterator it = templateUsage.begin();
       it != templateUsage.end(); ++it)
  {
    usageList.append(QPair<int, QString>(it.value(), it.key()));
  }
  qGreater<QPair<int, QString> > lt;
  qSort(usageList.begin(), usageList.end(), lt);
  return usageList;
}

static void
escapeTemplateSyntax(QString &text)
{
  text.replace("|", PIPE_ESCAPE).replace("=", EQUALS_ESCAPE)
    .replace("{", LEFT_BRACE_ESCAPE).replace("}", RIGHT_BRACE_ESCAPE);
}

static void
unescapeTemplateSyntax(QString &text)
{
  text.replace(PIPE_ESCAPE, "|").replace(EQUALS_ESCAPE, "=")
    .replace(LEFT_BRACE_ESCAPE, "{").replace(RIGHT_BRACE_ESCAPE, "}");
}

/// Returns the index position of the first occurrence of the string str
/// in the string text, searching forward from index position from and
/// skipping the contents of embedded wikilinks.
/// @return
///   - if str is not found in text.
static int
linkSkippingIndexOf(const QString &text,
                    const QString &str,
                    int from)
{
  if (from < 0)
    from += text.length();

  int linkLevel = 0;
  for (int i = from; i < text.length(); ++i)
  {
    // Handle opening a link.
    if (text.midRef(i, 2) == "[[")
    {
      ++linkLevel;
      ++i;
      continue;
    }

    // Handle closing a link.
    if (linkLevel > 0 && text.midRef(i, 2) == "]]")
    {
      --linkLevel;
      ++i;
      continue;
    }

    if (linkLevel == 0 && text.midRef(i, str.length()) == str)
      return i;
  }

  return -1;
}

static QString
removeTemplates(QString wikiText,
                const ParameterList &params,
                const QString &pageName,
                bool &pageNameUsed,
                QMap<QString, QString> &entryCache,
                Format2Reader &reader,
                bool updateTemplateUsage,
                bool debug)
{
  int from = -1;
  pageNameUsed = false;

  // find a pair
  while (true)
  {
    int start3 = wikiText.lastIndexOf("{{{", from);
    int start2 = wikiText.lastIndexOf("{{", from);
    if (start3 == -1 && start2 == -1)
    {
      unescapeTemplateSyntax(wikiText);
      return wikiText;
    }

    // Handle a case of rightmost start2
    if (start3 == -1 || start2 > start3 + 1)
    {
      int stop = linkSkippingIndexOf(wikiText, "}}", start2);
      if (stop == -1)
      {
        // We are on the beginning, search no more. start is 0 or 1
        if (start2 < 2)
        {
          unescapeTemplateSyntax(wikiText);
          return wikiText;
        }

        from = qMax(start2 - 1, 0);
        continue;
      }
      bool pageNameUsedLocal;
      evaluateTemplate(wikiText, start2, stop + 2,
                       pageName, pageNameUsedLocal, entryCache, reader,
                       updateTemplateUsage, debug);

      if (pageNameUsedLocal)
        pageNameUsed = true;
      from = qMax(start2 - 1, 0);
    }
    // Handle a case of rightmost start3
    else
    {
      int stop3 = linkSkippingIndexOf(wikiText, "}}}", start3);
      int stop2 = linkSkippingIndexOf(wikiText, "}}", start3);
      if (stop3 == -1 || (stop2 != -1 && stop2 < stop3))
      {
        // Try to expand the last {{
        if (stop2 >= 0)
        {
          bool pageNameUsedLocal;
          evaluateTemplate(wikiText, start3 + 1, stop2 + 2,
                           pageName, pageNameUsed, entryCache, reader,
                           updateTemplateUsage, debug);

          if (pageNameUsedLocal)
            pageNameUsed = true;

          from = qMax(start3, 0);
        }
        else
        {
          if (start3 < 2)
          {
            // We are on the beginning, search no more.
            // start is 0 or 1
            unescapeTemplateSyntax(wikiText);
            return wikiText;
          }

          // Wikisyntax is broken.
          // Search another pair..
          from = qMax(start3 - 1, 0);
        }
        continue;
      }

      QString contents = wikiText.mid(start3 + 3, stop3 - start3 - 3);
      QString evaluated = TemplateUtils::evaluateParameter(contents, params);
      if (debug)
        cstdout("Param: " + contents + " -> " + evaluated);
      escapeTemplateSyntax(evaluated);
      wikiText.replace(start3, stop3 + 3 - start3, evaluated);
      from = qMax(start3 - 1, 0);
    }
  }
}

/// Gets a template call from entry text, calls the template,
/// and merges the result into the entry text. The modified entry text is
/// returned.
/// @param from
///   Position at the beginning of {{template..}}, pointing to the first {.
/// @param to
///   Position at the end of template, pointing after the last }.
static void
evaluateTemplate(QString &wikiText,
                 int from,
                 int to,
                 const QString &pageName,
                 bool &pageNameUsed,
                 QMap<QString, QString> &entryCache,
                 Format2Reader &reader,
                 bool updateTemplateUsage,
                 bool debug)
{
  QString contents = wikiText.mid(from + 2, to - from - 4);
  pageNameUsed = false;

  if (updateTemplateUsage)
  {
    QMap<QString, int>::const_iterator it = templateUsage.find(contents);
    if (it == templateUsage.end())
      templateUsage.insert(contents, 1);
    else
      templateUsage[contents] += 1;
  }

  // Check the entry cache for the result of evaluation. If it is not found,
  // evaluate the template.
  QString evaluated;
  QMap<QString, QString>::const_iterator crossEntryCacheIt = crossEntryCache.find(contents);
  if (crossEntryCacheIt == crossEntryCache.end())
  {
    QMap<QString, QString>::const_iterator entryCacheIt = entryCache.find(contents);
    if (entryCacheIt == entryCache.end()) // not found in entry cache
    {
      if (debug)
        cstdout("BEGIN Template: " + contents);

      // Store the information about the template being evaluated to
      // the entry cache.  This is used to detect loops.
      entryCache.insert(contents, "Wikt:TEMPLATE ENDLESS LOOP DETECTED");

      evaluated = evaluateTemplate(contents, pageName, pageNameUsed,
                                   entryCache, reader, updateTemplateUsage, debug);

      if (debug)
        cstdout("END Template: " + contents + " -> " + evaluated);

      escapeTemplateSyntax(evaluated);

      if (pageNameUsed)
        entryCache[contents] = evaluated;
      else
        crossEntryCache.insert(contents, evaluated);
    }
    else
      evaluated = entryCacheIt.value();
  }
  else
    evaluated = crossEntryCacheIt.value();

  // Results starting with "*", "#", ":", ";", and "{|" automatically
  // get a newline at the start.
  // Source: http://meta.wikimedia.org/wiki/Help:Newlines_and_spaces
  //         #Automatic_newline_at_the_start
  bool precedesNewline = (from > 0 && wikiText[from - 1] == '\n');
  bool startsWith = (evaluated.length() > 0 &&
                     (evaluated[0] == '*' || evaluated[0] == '#' ||
                      evaluated[0] == ':' || evaluated[0] == ';' ||
                      evaluated.startsWith(LEFT_BRACE_ESCAPE PIPE_ESCAPE)));
  if (!precedesNewline && startsWith)
      evaluated.prepend("\n");

  wikiText.replace(from, to - from, evaluated);
}

/// Returns the evaluated template content.
/// @param templateText
///   The text inside {{ and }}, containing template name and template
///   parameters. It must not contain any templates or template
///   parameters.
static QString
evaluateTemplate(const QString &templateText,
                 const QString &pageName,
                 bool &pageNameUsed,
                 QMap<QString, QString> &entryCache,
                 Format2Reader &reader,
                 bool updateTemplateUsage,
                 bool debug)
{
  pageNameUsed = false;
  QString templateTextTrimmed = templateText.trimmed();
  // Handle built-in templates #if, #switch etc.
  if (ParserFunctions::isParserFunction(templateTextTrimmed))
    return ParserFunctions::evaluate(templateText, reader, pageName, pageNameUsed);
  // Handle build-in templats uc:, ucfirst:, formatnum: etc.
  if (FormattingFunctions::isFormattingFunction(templateTextTrimmed))
    return FormattingFunctions::evaluate(templateText);
  // Handle built-in templates PAGENAME, PAGENAMEE, SUBPAGENAME etc.
  if (PageNameFunctions::isPageNameFunction(templateTextTrimmed))
  {
    pageNameUsed = true;
    return PageNameFunctions::evaluate(templateText, pageName);
  }
  // Handle built-in templates ns:, fullurl: etc.
  if (NamespaceUrlFunctions::isFunction(templateTextTrimmed))
    return NamespaceUrlFunctions::evaluate(templateText);

  // get template name
  // parse parameters and build parameter list
  QList<QString> parts;
  TemplateUtils::getParts(templateText, parts);
  // Return just the template name if it contains forbidden characters.
  if (parts[0].contains('[') || parts[0].contains(']'))
    return "&#x007b;&#x007b;" + parts[0] + "&#x007d;&#x007d;";
  if (parts[0].contains("DEFAULTSORT", Qt::CaseInsensitive)) // temporarily ignore
    return "";
  if (parts[0].contains("CURRENTYEAR"))
    return "2011";

  // Handle msg: and raw:
  // See http://meta.wikimedia.org/wiki/Help:Magic_words#Template_modifiers
  if (parts[0].startsWith("raw:") || parts[0].startsWith("msg:"))
    parts[0].remove(0, 4); // remove raw: and msg:

  // Handle templates with prefix "Special:" (case insensitive) in name:
  // those are not evaluated like templates, but are returned as a link.
  if (parts[0].startsWith("Special:", Qt::CaseInsensitive))
    return "[[:" + parts[0] + "]]";

  // Get template page name. If the name already contains
  // the "Template:" prefix, do not add it.
  QString templatePageName = parts[0];

  // Get the template contents.
  QString source;
  if (templatePageName.startsWith("Template:") && reader.exist(templatePageName))
    source = reader.sourceTemplate(templatePageName);
  else if (reader.exist("Template:" + templatePageName))
    source = reader.sourceTemplate("Template:" + templatePageName);
  else if (reader.exist(templatePageName) &&
           Namespace::instance().fromEntry(templatePageName) != Namespace::Main)
    source = reader.sourceTemplate(templatePageName);
  else
  {
    if (!templatePageName.startsWith("Template:"))
	templatePageName.prepend("Template:");

    return "&#x007b;&#x007b;" + templatePageName + "&#x007d;&#x007d;";
  }

  // If the template contain <onlyinclude></onlyinclude>, provide only
  // the text between those tags.
  // Can this block of code be moved to XmlToPrep processing?
  if (source.contains("<onlyinclude"))
  {
    static QRegExp includeTag("<onlyinclude\\s*>");
    static QRegExp includeEndTag("</onlyinclude\\s*>");
    int includeStart = includeTag.indexIn(source);
    if (includeStart != -1)
    {
      int includeEnd = includeEndTag.indexIn(source, includeStart);
      if (includeEnd != -1)
        source = source.mid(includeStart + includeTag.matchedLength(),
                            includeEnd - includeStart - includeTag.matchedLength());
      else
        source = source.mid(includeStart + includeTag.matchedLength());
    }
  }

  // Evaluate all parameters and templates inside.
  ParameterList params = TemplateUtils::getParameterList(parts);
  return removeTemplates(source, params, pageName, pageNameUsed,
                         entryCache, reader, updateTemplateUsage, debug);
}

QString
templateSolver(const QString &pageName,
               const QString &pageContent,
               Format2Reader &reader,
               bool updateTemplateUsage,
               bool debug)
{
  if (debug)
    cstdout(pageName);

  /// Evaluation cache for single entry.
  /// Key - template text
  /// Value - result
  QMap<QString, QString> entryCache;
  ParameterList emptyParams;
  bool pageNameUsed;
  return removeTemplates(pageContent, emptyParams,
                         pageName, pageNameUsed, entryCache,
                         reader, updateTemplateUsage, debug);
}
