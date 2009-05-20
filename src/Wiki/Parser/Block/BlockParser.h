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
#ifndef BLOCKPARSER_H_
#define BLOCKPARSER_H_

#include "../Prerequisites.h"

/// Parses a sequence of blocks.
/// Block is one of following:
///  * Preformatted block
///  * Heading
///  * List
///  * Div
///  * Paragraph
///  * Table
class BlockParser
{
public:
  // Parses till the end of the buffer.
  static void parse(Node &parent, Buffer &buffer);

protected:
  /// Tries to match every possible rule.
  /// @return
  ///   True if at least one rule matched.
  /// @param buffer
  ///   Input buffer.
  /// @return
  ///   Output node pointer. 0 if the parse cycle was not successful.
  static Node *parseCycle(Buffer &buffer);
};


#endif /* BLOCKPARSER_H_ */
