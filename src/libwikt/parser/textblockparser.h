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
#ifndef TEXTBLOCKPARSER_H_
#define TEXTBLOCKPARSER_H_

#include "prerequisites.h"

class TextBlockParser
{
public:
  /// Parses until it reaches the end of the buffer.
  /// @param node
  ///   Parent node.
  static void parse(Node &node, Buffer &buffer);
  static void parse(Node &node, const QString &text)
  {
    Buffer buffer(text);
    parse(node, buffer);
  }
};

#endif /* TEXTBLOCKPARSER_H_ */
