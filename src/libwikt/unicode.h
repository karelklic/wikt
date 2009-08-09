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
#ifndef LIBWIKT_UNICODE_H
#define LIBWIKT_UNICODE_H

#include <QString>
#include <string>

class Unicode
{
public:
  static std::string escape(const QString &contents);
  static QString unescape(const std::string &contents);
  static QString unescape(const QString &contents);

  // Unicode case-insensitive comparison
  // Source: http://qt.gitorious.org/qt/qt/blobs/raw/master/src/corelib/tools/qstring.cpp 2009-08-08
  static int ucstricmp(const ushort *a, const ushort *ae, const ushort *b, const ushort *be);
};

#endif

