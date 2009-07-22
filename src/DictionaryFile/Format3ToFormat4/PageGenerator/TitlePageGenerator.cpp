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
#include "TitlePageGenerator.h"
#include "../Format4Writer.h"
#include "../../../Version.h"
#include "../../../MainWindow/WebView/UrlUtils.h"

//===========================================================================
TitlePageGenerator::TitlePageGenerator() : _entryCount(0)
{
}

//===========================================================================
void TitlePageGenerator::visit(const QString &entryName)
{
  // Skip pages with a namespace.
  if (entryName.contains(':')) return;
  ++_entryCount;
}

//===========================================================================
void TitlePageGenerator::write(Format4Writer &destination)
{

  QString page;
  page +=
    "<html>"
    "<head>"
    "  <link rel=\"stylesheet\" type=\"text/css\" href=\"special://stylesheet\" />"
    "</head>"
    "<body>"
    "  <h1>Wikt <small>"WIKT_VERSION"</small></h1>";

  QString entryCount = QString::number(_entryCount);
  entryCount.insert(-6, ',');
  entryCount.insert(-3, ',');
  page += QString("  <p><a href=\"%1\">%2 entries</a> with English definitions from over 300 languages.</p>")
    .arg(UrlUtils::toUrl("Wikt:Statistics").toString())
    .arg(entryCount);

  page += QString(
    "  <p>Entries come from Wiktionary, a collaborative project to"
    "     produce a free-content multilingual dictionary. All the"
    "     content is licensed under both the "
    "     <a href=\"%1\">Creative Commons Attribution-ShareAlike 3.0 Unported License</a>"
    "     as well as the <a href=\"%2\">GNU Free Documentation License</a>.</p>"
    "</body>"
    "</html>")
    .arg(UrlUtils::toUrl("Wikt:Creative Commons Attribution-ShareAlike 3.0 Unported License").toString())
    .arg(UrlUtils::toUrl("Wikt:GNU Free Documentation License").toString());

  destination.addEntry("Wikt:Title Page", page);
}
