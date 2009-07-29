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
#include "UnitTestRunner.h"
//#include <UrlUtilsTest.h>
//#include <Wiki/Tree/Article/ArticleNodeTest.h>
//#include <Wiki/Tree/Link/LinkTargetNodeTest.h>
//#include <Wiki/Parser/TestList.h>
//#include <QTest>
#include <QFile>

//===========================================================================
void UnitTestRunner::run()
{
  #define TEST(__class) { __class c; QTest::qExec(&c); }

  //
  // Dom
  //
  /*TEST(ArticleNodeTest);
  TEST(LinkTargetNodeTest);
  //
  // Format2ToFormat3
  //
  TEST(FormattingFunctionsTest);
  TEST(TemplateUtilsTest);
  TEST(ParserFunctionsTest);
  TEST(PageNameFunctionsTest);
  TEST(TemplateSolverTest);
  TEST(NamespaceUrlFunctionsTest);
  // Format3ToFormat4
  TEST(LinkConverterTest);
  //
  // Parser
  //
  WIKI_PARSER_TEST_LIST;
  //
  TEST(UrlUtilsTest);*/
}
