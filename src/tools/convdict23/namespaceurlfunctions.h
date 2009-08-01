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
#ifndef NAMESPACE_URL_FUNCTIONS_H_
#define NAMESPACE_URL_FUNCTIONS_H_

#include <libwikt/prerequisites.h>
#include <QString>

/// Implements namespace and URL parser functions.
/// The following functions are implemented:
///  - {{ns:}}
///  - {{localurl:}}, {{localurle:}}
///  - {{fullurl:}}, {{fullurle:}}
///  - {{urlencode:}}
/// The following is to be implemented here if necessary:
///  - {{anchorencode:}}
///  - {{filepath:}}
class NamespaceUrlFunctions
{
public:
  /// @param templateText
  ///   MUST BE TRIMMED (this is optimalization)
  static bool isFunction(const QString &templateText);
  /// Evaluates the template text as a namespace or URL function.
  static QString evaluate(const QString &templateText);
};

#endif /* NAMESPACE_URL_FUNCTIONS_H_ */
