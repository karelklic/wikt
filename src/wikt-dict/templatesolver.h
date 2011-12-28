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

#include <QMap>
#include <QList>
#include <QPair>

class QString;
class Format2Reader;

/// Finds and evaluates all templates in a wiki page.
///
/// See http://meta.wikimedia.org/wiki/Help:Template
///
/// Use http://en.wiktionary.org/wiki/Special:ExpandTemplates to
/// check MediaWiki behavior.
///
/// @param pageName
///   Name of the evaluated page, including namespace if it is
///   different from Main.
/// @param pageContent
///   Content of the evaluated page in wiki format with template calls.
/// @param reader
///   A reader that provides access to all pages and templates referenced from
///   the evaluated page. This function does not change the contents of
///   the reader, It is not const because it caches access.
extern QString
templateSolver(const QString &pageName,
               const QString &pageContent,
               Format2Reader &reader,
               bool updateTemplateUsage,
               bool debug);

/// Filled only by templateSolver calls with
/// updateTemplateUsage == true.
/// The returned list is sorted from greatest usage.
extern QList<QPair<int, QString> >
templateUsageList();

extern QMap<QString, QString>
crossEntryCache;

#endif /* TEMPLATESOLVER_H_ */
