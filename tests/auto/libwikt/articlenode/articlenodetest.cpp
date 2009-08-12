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
#include <libwikt/tree/articlenode.h>
#include <libwikt/tree/headingnode.h>
#include <libwikt/tree/texttokennode.h>
#include <QTest>
#include <QObject>

class ArticleNodeTest : public QObject
{
  Q_OBJECT
private slots:
  void generateXHtmlTableOfContents0();
};

//===========================================================================
void ArticleNodeTest::generateXHtmlTableOfContents0()
{
  HeadingNode *head2 = new HeadingNode(2);
  head2->append(new TextTokenNode("English"));
  ArticleNode articleNode;
  articleNode.append(head2);

  //QCOMPARE(articleNode.generateXHtmlTableOfContents(), QString(""));
}

QTEST_APPLESS_MAIN(ArticleNodeTest)
#include "articlenodetest.moc"
