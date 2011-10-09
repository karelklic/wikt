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
#ifndef PARSERTEST_H
#define PARSERTEST_H
#include <QTest>
#include <QObject>

class ParserTest : public QObject
{
  Q_OBJECT
private slots:
  void blockHtmlParser_indexIn();
  /// "''abc'''d'''''"
  void boldItalic_embedded0();
  /// "'''abc''d'''''"
  void boldItalic_embedded1();
  /// "'''abc ''d'' '''"
  void boldItalic_embedded2();
  /// "'''''abc''d'''"
  void boldItalic_embedded3();
  /// "'''''abc'''d''"
  void boldItalic_embedded4();
  /// "'''''abc''''' not parsed"
  void boldItalic_embedded5();
  /// "''italic'''''bold'''"
  void boldItalic_embedded6();
  void bulletList_simpleList();
  void bulletList_embeddedList();
  void htmlEntity_nbsp();
  void inlineHtml_emptySpan();
  void inlineHtml_spanWithAttributes();
  /// Test the indexOfClosingTag method on all inputs.
  void inlineHtml_indexOfClosingTag();
  /// Test the parsing of <br clear="left" />
  void inlineHtml_brTag();
  void link_simple();
  void link_media();
  void link_withSpace();
  void link_withSlash();
  void numberedList_simple();
  void numberedList_embedded();
  void paragraph_startingWithLink();
  void paragraph_simple();
  void tableCell_simpleCells();
  void tableCell_simpleAttribCells();
  void tableCell_oneLineCells();
  void tableCell_multilineCell();
  void tableCell_embeddedTable();
  void table_simplest();
  void table_simpleWithHeader();
  void table_withTd();
};

#endif

