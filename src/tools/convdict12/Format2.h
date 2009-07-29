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
#ifndef ENTRYWRITER_H_
#define ENTRYWRITER_H_

#include <QString>

/// @param directory
///   The directory with a new contents for some entries.
void Format2_loadErrata(const QString &directory);

/// @brief Adds entry to the file.
///
/// Some entries may be ignored because of their namespace. Entries from Wiktionary
/// namespace are ignored for now.
///
/// The contents of the entry can be changed before saving.
///
/// Format2 modifies entry content:
///  - <nowiki> sections are converted to HTML entities and the tags are removed.
///  - <noinclude> blocks are removed with their content
///  - HTML comments <!-- --> are removed with their content
///  - <includeonly> tags are removed, but not the contents between them
///
/// @param name
///   Name of entry. Includes the optional namespace.
/// @param contents
///   Entry contents in wiki syntax.
void Format2_addEntry(const QString &name, QString contents);

void Format2_build(const QString &destinationFile);

#endif /* ENTRYWRITER_H_ */
