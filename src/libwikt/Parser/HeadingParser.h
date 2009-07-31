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
#ifndef HEADING_PARSER_H_
#define HEADING_PARSER_H_

#include "Prerequisites.h"

class HeadingParser
{
public:
  /// Returns 0 if the buffer contents cannot be
  /// parsed as a heading.
  static Node *parse(Buffer &buffer);
};

#endif /* HEADING_PARSER_H_ */
