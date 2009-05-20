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
#include <QTemporaryFile>
#include <vector>

/// @brief Creates an Format2 file.
///
/// The format2 files contain entries and indices in an entry-seekable manner.
/// Format2 also modifies entry content:
///  - <nowiki> sections are converted to HTML entities and the tags are removed.
///  - <noinclude> blocks are removed with their content
///  - HTML comments <!-- --> are removed with their content
///  - <includeonly> tags are removed, but not the contents between them
///
/// The Format2 file contains indices that point to the entries, and entries themeselves.
///
/// The Format2Writer uses temporary file for writing.
class Format2Writer
{
public:
  /// @brief Standard constructor.
  /// @param targetFileName
  ///   Destination file.
  Format2Writer(const QString &targetFileName);
  ~Format2Writer();

  /// @brief Adds entry to the file.
  ///
  /// Some entries may be ignored because of their namespace. Entries from Wiktionary
  /// namespace are ignored for now.
  ///
  /// The contents of the entry can be changed before saving.
  ///
  /// @param name
  ///   Name of entry. Includes the optional namespace.
  /// @param contents
  ///   Entry contents in wiki syntax.
  void addUnsortedEntry(const QString &name, const QString &contents);
  void close();

private:
  /// Destination file.
  QString _targetFileName;

  typedef std::pair<QString, size_t> Link;
  typedef std::vector<Link> LinkList;
  /// Offsets to entries.
  LinkList _links;

  /// Temporary file with entries without indices.
  QTemporaryFile _temporaryFile;
};

#endif /* ENTRYWRITER_H_ */
