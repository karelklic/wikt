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
#include <libwikt/format4reader.h>
#include <libwikt/parser/articleparser.h>
#include <QTextStream>
#include <QCoreApplication>
#include <QStringList>

//==============================================================================
int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);

  QStringList args = a.arguments();
  QString word = args.last();
  args.removeLast();
  bool exist = args.contains("--exists") || args.contains("--exist") || args.contains("-e");
  bool xml = args.contains("--xml") || args.contains("-x");

  QString dataPath = QCoreApplication::applicationDirPath() + "/../share/wikt/data";
  Format4Reader reader(dataPath + "/enwiktionary-20090923.ei4");
  QTextStream out(stdout, QIODevice::WriteOnly);
  if (xml)
  {
    QString source = reader.source(word);
    ArticleNode *node = ArticleParser::parse(word, source);
    out << node->toXml() << endl;
    delete node;
  }
  else
  {
    if (exist)
      out << (reader.exist(word) ? "Yes" : "No") << endl;
    else
      out << reader.source(word) << endl;
  }

  return 0;
}

