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
#ifndef BOLDITALICPARSERTEST_H_
#define BOLDITALICPARSERTEST_H_

#include <QObject>

/// Tests BoldItalicParser.
class BoldItalicParserTest : public QObject
{
  Q_OBJECT
private slots:
  /// "''abc'''d'''''"
  void embedded0();
  /// "'''abc''d'''''"
  void embedded1();
  /// "'''abc ''d'' '''"
  void embedded2();
  /// "'''''abc''d'''"
  void embedded3();
  /// "'''''abc'''d''"
  void embedded4();
  /// "'''''abc''''' not parsed"
  void embedded5();
  /// "''italic'''''bold'''"
  void embedded6();
};

#endif /* BOLDITALICPARSERTEST_H_ */
