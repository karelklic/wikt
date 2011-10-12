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
/* This file is required by commandMidToDict. */
#ifndef CATEGORYBUILDER_H
#define CATEGORYBUILDER_H

#include "format4writer.h"
#include <libwikt/tree/articlenode.h>
#include <QString>

/// Associates category contents with certain category.
/// @param contents
///   Contents in wiki markup.
void CatBuilder_addContents(const QString &categoryName, const QString &contents);

/// Processes entry wiki markup and adds entry to all categories where it belongs.
void CatBuilder_process(const QString &name, const ArticleNode &node);

/// Writes the categories to the output file.
void CatBuilder_writeAll(Format4Writer &destination);

#endif
