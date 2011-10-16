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
#include <libwikt/format4reader.h>
#include <libwikt/parser/articleparser.h>
#include <QTextStream>
#include <cstdlib>

void commandMidSource(const QString &midFile,
                      const QString &entry)
{
  Format3Reader reader(midFile);
  if (!reader.exist(entry))
    exit(1);

  QTextStream out(stdout, QIODevice::WriteOnly);
  out << reader.sourceDirect(reader.entries().value(entry)) << endl;
}

void commandDictSource(const QString &dictFile,
                       const QString &entry,
                       bool xml)
{
  Format4Reader reader(dictFile);
  if (!reader.exist(entry))
    exit(1);

  QTextStream out(stdout, QIODevice::WriteOnly);
  QString source = reader.source(entry);
  if (xml)
  {
    ArticleNode *node = ArticleParser::parse(entry, source);
    out << node->toXml() << endl;
    delete node;
  }
  else
    out << source << endl;
}
