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

#include "BufferTest.h"
#include "HeadingParserTest.h"
#include "HtmlEntityParserTest.h"
#include "InlineHtmlParserTest.h"
#include "LinkParserTest.h"
#include "BulletListParserTest.h"
#include "ListParserTest.h"
#include "NumberedListParserTest.h"
#include "ParagraphParserTest.h"
#include "TableParserTest.h"
#include "TableCellParserTest.h"
#include "TextBlockParserTest.h"
#include "BoldItalicParserTest.h"

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
