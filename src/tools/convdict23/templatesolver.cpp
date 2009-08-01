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
#include "templatesolver.h"
#include "namespaceurlfunctions.h"
#include "templateutils.h"
#include "parserfunctions.h"
#include "formattingfunctions.h"
#include "pagenamefunctions.h"
#include <libwikt/prerequisites.h>
#include <QRegExp>
#include <QTextStream>

//#define TEMPLATE_SOLVER_DEBUG

//===========================================================================
TemplateSolver::TemplateSolver(const QString &pageName,
    const QString &pageContent, Format2Reader &reader)
  : _pageName(pageName), _pageContent(pageContent), _reader(reader)
{
}

//===========================================================================
QString TemplateSolver::run()
{
#ifdef TEMPLATE_SOLVER_DEBUG
  COUT(_pageName);
#endif
  ParameterList empty;
  return removeTemplates(_pageContent, empty);
}

//===========================================================================
QString TemplateSolver::escapeTemplateSyntax(QString text)
{
#define PIPE_ESCAPE "1P#-"
#define LEFT_BRACE_ESCAPE "1L#-"
#define EQUALS_ESCAPE "1E#0-"
#define RIGHT_BRACE_ESCAPE "1R#-"
  return text.replace("|", PIPE_ESCAPE).replace("=", EQUALS_ESCAPE)
    .replace("{", LEFT_BRACE_ESCAPE).replace("}", RIGHT_BRACE_ESCAPE);
}

//===========================================================================
QString TemplateSolver::unescapeTemplateSyntax(QString text)
{
  return text.replace(PIPE_ESCAPE, "|").replace(EQUALS_ESCAPE, "=")
    .replace(LEFT_BRACE_ESCAPE, "{").replace(RIGHT_BRACE_ESCAPE, "}");
}

//===========================================================================
/// Returns the index position of the first occurrence of the string str
/// in the string text, searching forward from index position from and
/// skipping the contents of embedded wikilinks.
/// @return
///   - if str is not found in text.
int TemplateSolver::linkSkippingindexOf(const QString &text, const QString &str, int from)
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

//===========================================================================
QString TemplateSolver::removeTemplates(QString wikiText, const ParameterList &params)
{
  PROFILER;
  int from = -1;

  // find a pair
  while (true)
  {
    int start3 = wikiText.lastIndexOf("{{{", from);
    int start2 = wikiText.lastIndexOf("{{", from);
    if (start3 == -1 && start2 == -1)
      return unescapeTemplateSyntax(wikiText);

    // Handle a case of rightmost start2
    if (start3 == -1 || start2 > start3 + 1)
    {
      int stop = linkSkippingindexOf(wikiText, "}}", start2);
      if (stop == -1)
      {
        // We are on the beginning, search no more. start is 0 or 1
        if (start2 < 2)
          return unescapeTemplateSyntax(wikiText);

        from = qMax(start2 - 1, 0);
        continue;
      }
      evaluateTemplate(wikiText, start2, stop + 2);
      from = qMax(start2 - 1, 0);
    }
    // Handle a case of rightmost start3
    else
    {
      int stop3 = linkSkippingindexOf(wikiText, "}}}", start3);
      int stop2 = linkSkippingindexOf(wikiText, "}}", start3);
      if (stop3 == -1 || (stop2 != -1 && stop2 < stop3))
      {
        // Try to expand the last {{
        if (stop2 >= 0)
        {
          evaluateTemplate(wikiText, start3 + 1, stop2 + 2);
          from = qMax(start3, 0);
        }
        else
        {
          // We are on the beginning, search no more.
          // start is 0 or 1
          if (start3 < 2)
            return unescapeTemplateSyntax(wikiText);

          // Search another pair.
          from = qMax(start3, 0);
        }
        continue;
      }

      QString contents = wikiText.mid(start3 + 3, stop3 - start3 - 3);
      QString evaluated = TemplateUtils::evaluateParameter(contents, params);
#ifdef TEMPLATE_SOLVER_DEBUG
      COUT("Param: " + contents + " -> " + evaluated);
#endif
      wikiText.replace(start3, stop3 + 3 - start3, escapeTemplateSyntax(evaluated));
      from = qMax(start3 - 1, 0);
    }
  }
}

//===========================================================================
void TemplateSolver::evaluateTemplate(QString &wikiText, int from, int to)
{
  PROFILER;
  QString contents = wikiText.mid(from + 2, to - from - 4);

  // Check the cache for the result of evaluation. If it is not found,
  // evaluate the template.
  QString evaluated;
  QMap<QString, QString>::const_iterator it = _cache.find(contents);
  if (it == _cache.end()) // not found in cache
  {
    #ifdef TEMPLATE_SOLVER_DEBUG
      COUT("BEGIN Template: " + contents);
    #endif
    evaluated = evaluateTemplate(contents);
    #ifdef TEMPLATE_SOLVER_DEBUG
      COUT("END Template: " + contents + " -> " + evaluated);
    #endif
  
    evaluated = escapeTemplateSyntax(evaluated);
    _cache.insert(contents, evaluated);
  }
  else
    evaluated = it.value();

  // Results starting with "*", "#", ":", ";", and "{|" automatically
  // get a newline at the start.
  // Source: http://meta.wikimedia.org/wiki/Help:Newlines_and_spaces#Automatic_newline_at_the_start
  bool precedesNewline = (from > 0 && wikiText[from - 1] == '\n');
  bool startsWith = (evaluated.length() > 0 && (evaluated[0] == '*' || evaluated[0] == '#' || evaluated[0] == ':' || evaluated[0] == ';' || evaluated.startsWith(LEFT_BRACE_ESCAPE PIPE_ESCAPE)));
  if (!precedesNewline && startsWith)
      evaluated.prepend("\n");
  
  wikiText.replace(from, to - from, evaluated);
}

//===========================================================================
QString TemplateSolver::evaluateTemplate(const QString &templateText)
{
  QString templateTextTrimmed = templateText.trimmed();
  // Handle built-in templates #if, #switch etc.
  if (ParserFunctions::isParserFunction(templateTextTrimmed))
    return ParserFunctions::evaluate(templateText, _reader, _pageName);
  // Handle build-in templats uc:, ucfirst: etc.
  if (FormattingFunctions::isFormattingFunction(templateTextTrimmed))
    return FormattingFunctions::evaluate(templateText);
  // Handle built-in templates PAGENAME, PAGENAMEE, SUBPAGENAME etc.
  if (PageNameFunctions::isPageNameFunction(templateTextTrimmed))
    return PageNameFunctions::evaluate(templateText, _pageName);
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
    return "2009";

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
  if (!templatePageName.startsWith("Template:"))
    templatePageName = "Template:" + templatePageName;

  // Get the template contents.
  QString source = _reader.source(templatePageName);
  if (source == "")
  {
    if (!_reader.exist(templatePageName))
      return "&#x007b;&#x007b;" + templatePageName + "&#x007d;&#x007d;";
    else
      return "";
  }

  // If the template contain <onlyinclude></onlyinclude>, provide only
  // the text between those tags.
  // Can this block of code be moved to XmlToEic processing?
  QString includeTag("<onlyinclude>");
  int includeStart = source.indexOf(includeTag);
  int includeEnd = source.indexOf("</onlyinclude>");
  if (includeStart != -1 && includeEnd != -1)
  {
    source = source.mid(includeStart + includeTag.length(),
      includeEnd - includeStart - includeTag.length());
  }

  // Evaluate all parameters and templates inside.
  ParameterList params = TemplateUtils::getParameterList(parts);
  return removeTemplates(source, params);
}
