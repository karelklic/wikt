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

int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);

  QString fileName = a.arguments().last();
  QFile file(fileName);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString source = QString::fromUtf8(file.readAll());

  QTextStream out(stdout, QIODevice::WriteOnly);
  ArticleNode *node = ArticleParser::parse("", source);
  out << node->toXml() << endl;
  delete node;

  return 0;
}

