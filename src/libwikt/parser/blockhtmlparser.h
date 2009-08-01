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
#ifndef DIVHTMLPARSER_H_
#define DIVHTMLPARSER_H_

#include "prerequisites.h"

/// Parser HTML block tags such as DIV and CENTER.
class BlockHtmlParser
{
public:
  /// Returns 0 if the buffer contents cannot be
  /// parsed as a DIV.
  static HtmlElementNode *parse(Buffer &buffer);

  static int indexIn(const QString &text, int offset = 0);

protected:
  /// Try to parse just one tag.
  /// @return
  ///   A valid node if parsing has been successful.
  ///   0 if no parse was successful.
  static HtmlElementNode *parse(Buffer &buffer, const QString &tag);
};

#endif /* DIVHTMLPARSER_H_ */
