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
#ifndef DEFINITIONLISTPARSER_H_
#define DEFINITIONLISTPARSER_H_

#include "prerequisites.h"

class DefinitionListParser
{
public:
  /// Returns 0 if the buffer contents cannot be
  /// parsed as a bullet list.
  static DefinitionListNode *parse(Buffer &buffer);
};

#endif /* DEFINITIONLISTPARSER_H_ */
