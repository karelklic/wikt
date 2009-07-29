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
#ifndef PAGENAMEFUNCTIONS_H_
#define PAGENAMEFUNCTIONS_H_

#include <libwikt/Prerequisites.h>
#include <QString>

/// Implements the following functions:
///  - {{SERVER}}, {{SERVERNAME}}
///  - {{PAGENAME}}, {{PAGENAMEE}}
///  - {{BASEPAGENAME}}, {{BASEPAGENAMEE}}
///  - {{SUBPAGENAME}}, {{SUBPAGENAMEE}}
///  - {{FULLPAGENAME}}, {{FULLPAGENAMEE}}
///  - {{NAMESPACE}}, {{NAMESPACEE}}
/// The following functions are not implemented, but if they
/// become required, they should be implemented here:
///  - {{TALKSPACE}}
///  - {{SUBJECTSPACE}}
///  - {{ARTICLESPACE}}
///  - {{TALKPAGENAME}}
///  - {{SUBJECTPAGENAME}}
///  - {{ARTICLEPAGENAME}}
class PageNameFunctions
{
public:
  /// @param templateText
  ///   MUST BE TRIMMED (this is optimalization)
  static bool isPageNameFunction(const QString &templateText);
  /// Evaluates the template text as a page name function.
  /// @param pageName
  ///   Full page name, eg. "Help:Magic words".
  static QString evaluate(const QString &templateText, const QString &pageName);
};

#endif /* PAGENAMEFUNCTIONS_H_ */
