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
#include <linkconverter.h>
#include <libwikt/format3reader.h>
#include <libwikt/mediareader.h>
#include <QTest>
#include <QObject>

/// Tests LinkConverter methods.
class LinkConverterTest : public QObject
{
  Q_OBJECT
private slots:
  void basicLinks();
  void linksWithNamespaces();
  void linksWithSlashes();
};

//===========================================================================
class LinkConverterTestReader : public Format3Reader
{
public:
  // Key: name, Value: contents.
  QMap<QString, QString> _data;
  // Contents that can be accessed by index.
  QList<QString> _contents;

  // Adds data to the reader.
  void add(const QString &name, const QString &contents)
  {
    _data.insert(name, contents);
    _contents.append(contents);
  }

  virtual bool exist(QString entryName) { return _data.contains(entryName); }
  virtual QString source(quint32 offset) { return _contents[offset]; }
  virtual QString sourceDirect(qint64 offset) { return _contents[offset]; }
};

//===========================================================================
class LinkConverterTestMediaReader : public MediaReader
{
};


//===========================================================================
void LinkConverterTest::basicLinks()
{
  LinkConverterTestReader reader;
  reader.add("Test", "Link [[existing]] and [[nonexisting]].");
  reader.add("existing", "some contents");
  LinkConverterTestMediaReader mediaReader;
  LinkConverter converter(reader, mediaReader);
  QString contents = converter.convertedContents(0);
  QCOMPARE(contents, QString("Link [[existing]] and nonexisting."));
}

//===========================================================================
void LinkConverterTest::linksWithNamespaces()
{
  LinkConverterTestReader reader;
  reader.add("Test", "Link [[Category:existing|e]] and [[Talk:nonexisting]].");
  reader.add("Category:existing", "some contents");
  reader.add("nonexisting", "some contents non existing");
  LinkConverterTestMediaReader mediaReader;
  LinkConverter converter(reader, mediaReader);
  QString contents = converter.convertedContents(0);
  QCOMPARE(contents, QString("Link [[Category:existing|e]] and Talk:nonexisting."));
}

//===========================================================================
void LinkConverterTest::linksWithSlashes()
{
  LinkConverterTestReader reader;
  reader.add("Wikisaurus:penis", "Link [[Wikisaurus:penis/more|e]] and [[Wikisaurus:penis/more2]].");
  reader.add("Wikisaurus:penis/more", "some contents");
  LinkConverterTestMediaReader mediaReader;
  LinkConverter converter(reader, mediaReader);
  QString contents = converter.convertedContents(0);
  QCOMPARE(contents, QString("Link [[Wikisaurus:penis/more|e]] and Wikisaurus:penis/more2."));
}

QTEST_APPLESS_MAIN(LinkConverterTest)
#include "linkconvertertest.moc"
