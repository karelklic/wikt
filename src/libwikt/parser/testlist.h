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

#include "buffertest.h"
#include "headingparsertest.h"
#include "htmlentityparsertest.h"
#include "inlinehtmlparsertest.h"
#include "linkparsertest.h"
#include "bulletlistparsertest.h"
#include "listparsertest.h"
#include "numberedlistparsertest.h"
#include "paragraphparsertest.h"
#include "tableparsertest.h"
#include "tablecellparsertest.h"
#include "textblockparsertest.h"
#include "bolditalicparsertest.h"

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
