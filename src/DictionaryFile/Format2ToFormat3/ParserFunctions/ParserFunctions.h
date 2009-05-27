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
#ifndef PARSERFUNCTIONS_H_
#define PARSERFUNCTIONS_H_

#include <QString>
#include "../Format2Reader.h"

/// The MediaWiki ParserFunctions extension provides ten additional
/// parser functions to supplement the "magic words", which are already
/// present in MediaWiki. All the parser functions provided by this
/// extension take the form:
/// {{ #functionname: argument 1 | argument 2 | argument 3 ... }}
class ParserFunctions
{
public:
  static bool isParserFunction(const QString &templateText);
  static QString evaluate(const QString &templateText, Format2Reader &reader,
      const QString &entryName);
};

#endif /* PARSERFUNCTIONS_H_ */
