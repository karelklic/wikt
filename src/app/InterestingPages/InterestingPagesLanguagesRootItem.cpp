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
#include "InterestingPagesLanguagesRootItem.h"
#include "InterestingPagesLinkItem.h"
#include "../MainWindow/MainWindow.h"
#include <libwikt/Wiki/WikiSource.h>
#include <libwikt/Wiki/Language/Language.h>

namespace InterestingPages {

//===========================================================================
LanguagesRootItem::LanguagesRootItem(Item *parent) : Item(LanguagesOfTheWorld, parent)
{
  _itemData.append(QVariant("Language indexes"));

  // Somewhere in the future this code will be a part of dictionary generator
  // and the list of languages will be loaded from the dictionary.
  for (int i = 0; i < Language::Unknown; ++i)
  {
    QStringList languageNames = Language::instance().toNames((Language::Type)i);
    foreach (const QString &languageName, languageNames)
    {
      // Check for language index existence. Force WikiSource class
      // *not* to use cache, because we do a lot of tests and caching
      // slows the startup too much.
      QString pageName = "Index:" + languageName;
      if (MainWindow::instance()->wikiSource()->exist(pageName, false))
        addLanguage(languageName);
    }
  }
}

//===========================================================================
void LanguagesRootItem::addLanguage(const QString &languageName)
{
  appendChild(new LinkItem(languageName, "Index:" + languageName, this));
}

}

