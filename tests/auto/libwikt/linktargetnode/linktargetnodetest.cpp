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
#include <libwikt/tree/linktargetnode.h>
#include <QTest>
#include <QObject>

class LinkTargetNodeTest : public QObject
{
  Q_OBJECT
private slots:
  void language();
  void namespace_();
  void project();
};

//===========================================================================
void LinkTargetNodeTest::language()
{
  LinkTargetNode a("apple");
  QCOMPARE(a.language(), Language::English);
  LinkTargetNode b("de:apple");
  QCOMPARE(b.language(), Language::German);
}

//===========================================================================
void LinkTargetNodeTest::namespace_()
{
  LinkTargetNode a("apple");
  QCOMPARE(a.namespace_(), Namespace::Main);
  LinkTargetNode b("Image talk:apple");
  QCOMPARE(b.namespace_(), Namespace::ImageTalk);
  LinkTargetNode c(" Category: automotive");
  QCOMPARE(c.namespace_(), Namespace::Category);
  QCOMPARE(c.entry(), QString("automotive"));
}

//===========================================================================
void LinkTargetNodeTest::project()
{
  LinkTargetNode a("apple");
  QCOMPARE(a.project(), Project::Wiktionary);
  LinkTargetNode b("w:apple");
  QCOMPARE(b.project(), Project::Wikipedia);
}

QTEST_APPLESS_MAIN(LinkTargetNodeTest)
#include "linktargetnodetest.moc"
