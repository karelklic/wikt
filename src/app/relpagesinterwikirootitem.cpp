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
#include "relpagesinterwikirootitem.h"
#include "relpagesexternallinkitem.h"
#include <libwikt/tree/node.h>
#include <libwikt/tree/paragraphnode.h>
#include <libwikt/tree/linknode.h>
#include <libwikt/tree/linktargetnode.h>
#include <QUrl>

namespace RelatedPages {

InterwikiRootItem::InterwikiRootItem(Item *parent)
  : Item(InterwikiRoot, parent)
{
  _itemData.append(QVariant("Interwiki"));
}

void InterwikiRootItem::fill(const Node *rootNode)
{
  QList<const LinkNode*> links;
  rootNode->findChildren(links);
  foreach(const LinkNode *link, links)
  {
    if (!link->isInterwiki()) continue;

    QString id = link->target().toText().section(':', 0, 0);
    QString iwiki = link->target().toText().section(':', 1);
    ExternalLinkItem *item = new ExternalLinkItem(
        link->xhtmlTitle() + " " + QChar(0x21d7),
        QUrl("http://" + id + ".wiktionary.org/wiki/" + iwiki),
        this);
    appendChild(item);
  }
}

}
