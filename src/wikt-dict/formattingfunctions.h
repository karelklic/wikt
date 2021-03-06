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
/* This file is required by commandPrepToMid. */
#ifndef FORMATTINGFUNCTIONS_H_
#define FORMATTINGFUNCTIONS_H_

#include <QString>

/// @brief Handles formatting functions lc, lcfirst, uc, ucfirst, formatnum.
///
/// @todo Support #dateformat, #formatdate, padleft, padright, plural, grammar.
///
/// See http://www.mediawiki.org/wiki/Help:Magic_words#Formatting.
/// See http://meta.wikimedia.org/wiki/Help:Magic_words#Formatting
class FormattingFunctions
{
public:
  /// @param templateText
  ///   MUST BE TRIMMED (this is optimalization)
  static bool isFormattingFunction(const QString &templateText);

  /// @param templateText
  static QString evaluate(const QString &templateText);
};

#endif /* FORMATTINGFUNCTIONS_H_ */
