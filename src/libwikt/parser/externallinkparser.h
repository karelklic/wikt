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
#ifndef EXTERNALLINKPARSER_H_
#define EXTERNALLINKPARSER_H_

#include "prerequisites.h"

/// Parses external links. This links has format [http://url/ title].
class ExternalLinkParser
{
public:
  /// Checks if buffer's content can be interpreted as an external link.
  /// @param buffer
  ///   Buffer is not changed if parsing is not successful. This is indicated
  ///   by returning 0.
  ///   Buffer's position is moved after the link if it was parsed and
  ///   returned.
  /// @return
  ///   Returns 0 if the buffer contents cannot be
  ///   parsed as a link.
  ///   Returns new link node when successfully parsed the buffer
  ///   at current position.
  static ExternalLinkNode *parse(Buffer &buffer);
};

#endif /* EXTERNALLINKPARSER_H_ */
