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
#include "TemplateSolver.h"
#include "../NamespaceUrlFunctions/NamespaceUrlFunctions.h"
#include "../TemplateUtils/TemplateUtils.h"
#include "../ParserFunctions/ParserFunctions.h"
#include "../FormattingFunctions/FormattingFunctions.h"
#include "../PageNameFunctions/PageNameFunctions.h"
#include "../../../Prerequisites.h"
#include <QRegExp>

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
  log("Starting template solver for \"" + _pageName + "\".");
  COUT(_pageName);
#endif
  ParameterList empty;
  return removeTemplates(_pageContent, empty);
}

//===========================================================================
static QString escapeTemplateSyntax(QString text)
{
  return text.replace("|", "pipeEscapeSure").replace("=", "equalsEscapeSure")
    .replace("{", "leftBraceEscapeSure").replace("}", "rightBraceEscapeSure");
}

//===========================================================================
static QString unescapeTemplateSyntax(QString text)
{
  return text.replace("pipeEscapeSure", "|").replace("equalsEscapeSure", "=")
    .replace("leftBraceEscapeSure", "{").replace("rightBraceEscapeSure", "}");
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
      int stop = wikiText.indexOf("}}", start2);
      if (stop == -1)
      {
        // We are on the beginning, search no more. start is 0 or 1
        if (start2 < 2)
          return unescapeTemplateSyntax(wikiText);

        from = start2 - 1;
        continue;
      }
      evaluateTemplate(wikiText, start2, stop + 2);
    }
    // Handle a case of rightmost start3
    else
    {
      int stop3 = wikiText.indexOf("}}}", start3);
      int stop2 = wikiText.indexOf("}}", start3);
      if (stop3 == -1 || (stop2 != -1 && stop2 < stop3))
      {
        // Try to expand the last {{
        if (stop2 >= 0)
          evaluateTemplate(wikiText, start3 + 1, stop2 + 2);
        else
        {
          // We are on the beginning, search no more.
          // start is 0 or 1
          if (start3 < 2)
            return unescapeTemplateSyntax(wikiText);

          // Search another pair.
          from = start3 - 1;
        }
        continue;
      }

      QString contents = wikiText.mid(start3 + 3, stop3 - start3 - 3);
      QString evaluated = TemplateUtils::evaluateParameter(contents, params);
#ifdef TEMPLATE_SOLVER_DEBUG
      COUT("Param: " + contents + " -> " + evaluated);
#endif
      QString begin = wikiText.mid(0, start3);
      QString end = wikiText.mid(stop3 + 3);
      wikiText = begin + escapeTemplateSyntax(evaluated) + end;
    }
  }
}

//===========================================================================
void TemplateSolver::evaluateTemplate(QString &wikiText, int from, int to)
{
  PROFILER;
  QString begin = wikiText.mid(0, from);
  QString end = wikiText.mid(to);

  QString contents = wikiText.mid(from + 2, to - from - 4);
#ifdef TEMPLATE_SOLVER_DEBUG
  COUT("BEGIN Template: " + contents);
#endif
  QString evaluated = evaluateTemplate(contents);
#ifdef TEMPLATE_SOLVER_DEBUG
  COUT("END Template: " + contents + " -> " + evaluated);
#endif

  // Results starting with "*", "#", ":", ";", and "{|" automatically
  // get a newline at the start.
  // Source: http://meta.wikimedia.org/wiki/Help:Newlines_and_spaces#Automatic_newline_at_the_start
  if (evaluated.startsWith("*") || evaluated.startsWith("#") || evaluated.startsWith(":") ||
      evaluated.startsWith(";") || evaluated.startsWith("{|"))
  {
    if (!begin.endsWith("\n"))
      evaluated = "\n" + evaluated;
  }

  wikiText = begin + escapeTemplateSyntax(evaluated) + end;
}

//===========================================================================
QString TemplateSolver::evaluateTemplate(QString templateText)
{
  // Handle built-in templates #if, #switch etc.
  if (ParserFunctions::isParserFunction(templateText))
    return ParserFunctions::evaluate(templateText, _reader, _pageName);
  // Handle build-in templats uc:, ucfirst: etc.
  if (FormattingFunctions::isFormattingFunction(templateText))
    return FormattingFunctions::evaluate(templateText);
  // Handle built-in templates PAGENAME, PAGENAMEE, SUBPAGENAME etc.
  if (PageNameFunctions::isPageNameFunction(templateText))
    return PageNameFunctions::evaluate(templateText, _pageName);
  // Handle built-in templates ns:, fullurl: etc.
  if (NamespaceUrlFunctions::isFunction(templateText))
    return NamespaceUrlFunctions::evaluate(templateText);

  // get template name
  // parse parameters and build param list
  QList<QString> parts;
  TemplateUtils::getParts(templateText, parts);
  // Return just the template name if it contains forbidden characters.
  if (parts[0].contains('[') || parts[0].contains(']'))
    return "&#x007b;&#x007b;" + parts[0] + "&#x007d;&#x007d;";
  if (parts[0] == "rfc") // ignored template. TODO: systematic way to handle it
    return "";
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
