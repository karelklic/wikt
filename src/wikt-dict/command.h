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
#ifndef WIKT_DICT_COMMAND_H
#define WIKT_DICT_COMMAND_H

#include <QString>

void commandXmlToPrep(const QString &xmlFile, const QString &prepFile,
                      const QString &errataDir);

void commandPrepToMid(const QString &prepFile, const QString &midFile,
                      qint64 from = -1, qint64 to = -1, bool showNames = false);

#endif
