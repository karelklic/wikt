/* This file is part of Wikt. -*- mode: c++; c-file-style: "wikt"; -*-
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
#include "interestingpagesrootitem.h"
#include "interestingpageslanguagesrootitem.h"
#include "interestingpageslinkitem.h"

namespace InterestingPages {

RootItem::RootItem() : Item(Root, 0)
{
  // We must have some data. Never displayed, but the tree view does not
  // work when the root node is empty.
  _itemData.append(QVariant("H1"));
}

void RootItem::generate()
{
  qDeleteAll(_childItems);
  _childItems.clear();

  appendChild(new LinkItem("Appendices", "Category:Appendices", this));
  appendChild(new LinkItem("Abbreviations", "Category:Abbreviations, acronyms and initialisms", this));
  appendChild(new LinkItem("Rhymes", "Rhymes:English", this));
  appendChild(new LinkItem("Phrasebooks", "Category:Phrasebook", this));

  _languagesOfTheWorld = new LanguagesRootItem(this);
  appendChild(_languagesOfTheWorld);

  appendChild(new LinkItem("Statistics", "Wikt:Statistics", this));
}

}

