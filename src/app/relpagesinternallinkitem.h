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
#ifndef RELATEDPAGESLOCALENTRYLINKITEM_H_
#define RELATEDPAGESLOCALENTRYLINKITEM_H_

#include "relpagesitem.h"
#include <QString>

namespace RelatedPages {

class InternalLinkItem : public Item
{
public:
  /// Standard constructor.
  /// @param entry
  ///   Serves as the title and the link.
  InternalLinkItem(const QString &entry, Item *parent);
  InternalLinkItem(const QString &title, const QString &link, Item *parent);

  const QString &link() const { return _link; }

protected:
  QString _link;
};

}

#endif /* RELATEDPAGESLOCALENTRYLINKITEM_H_ */
