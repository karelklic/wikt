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
#ifndef TEMPLATESOLVER_H_
#define TEMPLATESOLVER_H_

#include "format2reader.h"
#include "parameterlist.h"
#include <QObject>
#include <QString>

/// Finds and evaluates all templates in a wiki page.
///
/// See http://meta.wikimedia.org/wiki/Help:Template
///
/// Use http://en.wiktionary.org/wiki/Special:ExpandTemplates to
/// check MediaWiki behavior.
class TemplateSolver
{
  friend class TemplateSolverTest;
public:
  /// Standard constructor.
  /// @param pageName
  ///   Name of the evaluated page, including namespace if it is different from Main.
  /// @param pageContent
  ///   Content of the evaluated page in wiki format with template calls.
  /// @param reader
  ///   A reader that provides access to all pages and templates referenced from
  ///   the evaluated page.
  TemplateSolver(const QString &pageName, const QString &pageContent,
      Format2Reader &reader);

  QString run();

protected:
  /// Gets a template call from entry text, calls the template,
  /// and merges the result into the entry text. The modified entry text is
  /// returned.
  /// @param from
  ///   Position at the beginning of {{template..}}, pointing to the first {.
  /// @param to
  ///   Position at the end of template, pointing after the last }.
  void evaluateTemplate(QString &wikiText, int from, int to);

  /// Returns the evaluated template content.
  /// @param templateText
  ///   The text inside {{ and }}, containing template name and template parameters.
  ///   It must not contain any templates or template parameters.
  QString evaluateTemplate(const QString &templateText);

  QString removeTemplates(QString wikiText, const ParameterList &params);

  static QString escapeTemplateSyntax(QString text);
  static QString unescapeTemplateSyntax(QString text);
  static int linkSkippingindexOf(const QString &text, const QString &str, int from = 0);

  QString _pageName;
  QString _pageContent;

  /// Provides the template content.
  Format2Reader &_reader;

  /// Evaluation cache.
  /// Key - template text
  /// Value - result
  QMap<QString, QString> _cache;
};

#endif /* TEMPLATESOLVER_H_ */
