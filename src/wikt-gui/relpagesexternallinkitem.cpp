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
#include "relpagesexternallinkitem.h"
#include <QDesktopServices>

namespace RelatedPages {

ExternalLinkItem::ExternalLinkItem(const QString &title, const QUrl &url,
  Item *parent) : Item(ExternalLink, parent), _url(url)
{
  _itemData.append(title);
}

void ExternalLinkItem::openUrl() const
{
  QDesktopServices::openUrl(_url);
}

}
