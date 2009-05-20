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
#ifndef UNITTESTLIST_H_
#define UNITTESTLIST_H_

#include "Buffer/BufferTest.h"
#include "Heading/HeadingParserTest.h"
#include "Html/HtmlEntityParserTest.h"
#include "Html/InlineHtmlParserTest.h"
#include "Link/LinkParserTest.h"
#include "List/BulletListParserTest.h"
#include "List/ListParserTest.h"
#include "List/NumberedListParserTest.h"
#include "Paragraph/ParagraphParserTest.h"
#include "Table/TableParserTest.h"
#include "Table/TableCellParserTest.h"
#include "TextBlock/TextBlockParserTest.h"
#include "BoldItalic/BoldItalicParserTest.h"

#include <QTest>
template <typename T> void test() { T c; QTest::qExec(&c); }

#define WIKI_PARSER_TEST_LIST \
  test<BufferTest>(); \
  test<HeadingParserTest>(); \
  test<HtmlEntityParserTest>(); \
  test<InlineHtmlParserTest>(); \
  test<LinkParserTest>(); \
  test<BulletListParserTest>(); \
  test<ListParserTest>(); \
  test<NumberedListParserTest>(); \
  test<ParagraphParserTest>(); \
  test<TableParserTest>(); \
  test<TableCellParserTest>(); \
  test<BoldItalicParserTest>();

#endif /* UNITTESTLIST_H_ */
