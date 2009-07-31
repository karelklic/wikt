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
#ifndef RELATEDPAGESEXTERNALLINKSITEM_H_
#define RELATEDPAGESEXTERNALLINKSITEM_H_

#include "RelPagesItem.h"
#include <QString>
#include <QUrl>

namespace RelatedPages {

class ExternalLinkItem : public Item
{
public:
  /// Standard constructor.
  ExternalLinkItem(const QString &title, const QUrl &url, Item *parent);

  /// Opens the URL in external browser.
  void openUrl() const;

protected:
  QUrl _url;
};

}

#endif /* RELATEDPAGESEXTERNALLINKSITEM_H_ */
