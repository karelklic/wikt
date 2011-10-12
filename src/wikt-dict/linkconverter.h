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
#ifndef LINKCHECKINGPASS_H_
#define LINKCHECKINGPASS_H_

#include <QString>

class Format3Reader;
class MediaReader;

/// If a link links to other project (Wikipedia), it is transformed to
/// external link (http://...).
/// If a link links to other language variant (cs:something), and it is
/// not an interwiki link (not the same word as target), it is transformed to
/// external link.
/// If a link links to just another word, or a Talk page, or Category,
/// or Citations page, and the target page does not exist, the link is
/// transformed to plain text.
class LinkConverter
{
public:
  /// Standard constructor.
  LinkConverter(Format3Reader &reader, MediaReader &mediaReader);

  /// @param offs
  ///   Direct byte offset to an entry in file.
  QString convertedContents(qint64 offs);

protected:
  Format3Reader &_reader;
  MediaReader &_mediaReader;
};


#endif /* LINKCHECKINGPASS_H_ */
