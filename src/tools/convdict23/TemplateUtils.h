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
#ifndef TEMPLATEUTILS_H_
#define TEMPLATEUTILS_H_

#include <Prerequisites.h>
#include "ParameterList.h"
#include <QString>

class TemplateUtils
{
public:
  /// Gets all parts of a template call from the template text.
  /// Parts are not trimmed before added to the output list, except the first one,
  /// which represents template name.
  /// Example: getParts("a| b = i ") -> "a", " b = i "
  /// Example: getParts("a|b=[[wikipedia|w]]") -> "a", "b=[[wikipedia|w]]"
  /// @param output
  ///   Parts are added to this container. Container is not cleared
  ///   by this function.
  static void getParts(const QString &templateText, QList<QString> &output);

  static void _addParameterToList(const QString &paramText, ParameterList &dest);

  /// Builds a list of parameters from pre-parsed template call.
  /// @param parts
  ///   This function assumes that parts[0] contain template name.
  static ParameterList getParameterList(const QList<QString> &parts);

  /// @brief Evaluates parameters, such as {{{lang|en}}} -> en.
  /// @param parameterText
  ///   Parameter text without boundary {{{ }}}, eg. "lang|en".
  /// @param params
  ///   List of parameters passed to template call.
  static QString evaluateParameter(const QString &parameterText,
      const ParameterList &params);
};

#endif /* TEMPLATEUTILS_H_ */
