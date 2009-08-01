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
#ifndef STATSPAGEGENERATOR_H_
#define STATSPAGEGENERATOR_H_

#include "languagestatistic.h"
#include <libwikt/language.h>
#include <QString>
#include <QMap>
class Format4Writer;

/// Creates a wiki page with statistics.
class StatsPageGenerator
{
public:
  StatsPageGenerator();

  /// Counts an entry to the statistics.
  void visit(const QString &name, const QString &contents);

  void write(Format4Writer &destination);

protected:
  QMap<Language::Type, LanguageStatistic> _stats;
};

#endif /* STATSPAGEGENERATOR_H_ */
