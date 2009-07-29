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
#ifndef PARAGRAPH_H_
#define PARAGRAPH_H_

#include "../Prerequisites.h"

class ParagraphParser
{
public:
  /// Checks if the buffer contains a paragraph at current
  /// position. If it is so, parses it.
  /// @return
  ///   Returns 0 if the buffer contents at current position
  ///   cannot be parsed as a paragraph. Otherwise returns
  ///   new paragraph node and moves the buffer pointer after
  ///   the parsed text.
  ///
  ///   Caller owns the returned node and he is responsible
  ///   for its deleting.
  static ParagraphNode *parse(Buffer &buffer);

  /// Checks if the buffer contains a paragraph at current
  /// position. If it is so, parses it.
  /// This method does not create special paragraph node, but
  /// appends the paragraph contents.
  static bool parse(Node &parent, Buffer &buffer);

protected:
  /// @param line
  ///   Checked line without the line-ending character '\n'.
  /// @param currentParagraphText
  ///   The text which is already a part of paragraph and preceding this line.
  static bool lineBelongsToParagraph(const QString &line, const QString &currentParagraphText);
  static QString getText(Buffer &buffer);
};

#endif /* PARAGRAPH_H_ */
