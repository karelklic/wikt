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
#include "nodetest.h"
#include <libwikt/tree/articlenode.h>
#include <libwikt/tree/headingnode.h>
#include <libwikt/tree/texttokennode.h>
#include <libwikt/tree/linktargetnode.h>

void NodeTest::article_generateXHtmlTableOfContents0()
{
  HeadingNode *head2 = new HeadingNode(2);
  head2->append(new TextTokenNode("English"));
  ArticleNode articleNode;
  articleNode.append(head2);

  //QCOMPARE(articleNode.generateXHtmlTableOfContents(), QString(""));
}

void NodeTest::linkTarget_language()
{
  LinkTargetNode a("apple");
  QCOMPARE(a.language(), Language::English);
  LinkTargetNode b("de:apple");
  QCOMPARE(b.language(), Language::German);
}

void NodeTest::linkTarget_namespace()
{
  LinkTargetNode a("apple");
  QCOMPARE(a.namespace_(), Namespace::Main);
  LinkTargetNode b("Image talk:apple");
  QCOMPARE(b.namespace_(), Namespace::ImageTalk);
  LinkTargetNode c(" Category: automotive");
  QCOMPARE(c.namespace_(), Namespace::Category);
  QCOMPARE(c.entry(), QString("automotive"));
}

void NodeTest::linkTarget_project()
{
  LinkTargetNode a("apple");
  QCOMPARE(a.project(), Project::Wiktionary);
  LinkTargetNode b("w:apple");
  QCOMPARE(b.project(), Project::Wikipedia);
}

QTEST_APPLESS_MAIN(NodeTest)
