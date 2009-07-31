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
#ifndef INLINEHTMLPARSER_H_
#define INLINEHTMLPARSER_H_

#include "Prerequisites.h"

class InlineHtmlParser
{
  friend class BlockHtmlParser;
  friend class InlineHtmlParserTest;
public:
  /// Returns 0 if the buffer contents cannot be
  /// parsed as a inline HTML element.
  /// Inline elements are a part of text block,
  /// its SPAN, B, I, TT, SUB, SUP, BIG, SMALL, CITE etc.
  static HtmlElementNode *parse(Buffer &buffer);

protected:
  /// Try to parse just one tag.
  /// @return
  ///   A valid node if parsing has been successful.
  ///   0 if no parse was successful.
  static HtmlElementNode *parsePaired(Buffer &buffer, const QString &tag);
  /// Try to parse just one tag.
  /// @return
  ///   A valid node if parsing has been successful.
  ///   0 if no parse was successful.
  static HtmlElementNode *parseNonpaired(Buffer &buffer, const QString &tag);

  /// Finds the index of closing tag. Takes nested tags into account.
  /// @param buffer
  ///  Input buffer. Must contain also the opening tag for which we
  ///  search the closing tag.
  /// @param closingTagLength
  ///  If closing tag is found, its matched length is returned
  ///  to the referenced variable.
  /// @return
  ///   Returns -1 if tag was not found.
  ///   Returns offset to buffer to the beginning of the closing tag
  ///   if that was found.
  static int indexOfClosingTag(Buffer &buffer, const QString &tag,
      int &closingTagLength);
};

#endif /* INLINEHTMLPARSER_H_ */
