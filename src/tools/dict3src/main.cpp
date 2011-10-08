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
#include <libwikt/format3reader.h>
#include <QTextStream>
#include <QCoreApplication>
#include <QStringList>

int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);

  QStringList args = a.arguments();
  QString word = args.last();
  args.removeLast();
  bool exist = args.contains("--exists") || args.contains("--exist") || args.contains("-e");

  QString dataPath = QCoreApplication::applicationDirPath() + "/../share/wikt/data";
  Format3Reader reader(dataPath + "/enwiktionary-20090923.ei3");
  QTextStream out(stdout, QIODevice::WriteOnly);
  if (exist)
    out << (reader.exist(word) ? "Yes" : "No") << endl;
  else
    out << reader.sourceDirect(reader.entries().value(word)) << endl;

  return 0;
}

