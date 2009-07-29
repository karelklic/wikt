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
#include "LanguageStatistic.h"
#include <Wiki/Tree/Heading/HeadingNode.h>
#include <Wiki/Tree/List/ListItemNode.h>

//===========================================================================
LanguageStatistic::LanguageStatistic()
  : _entryCount(0), _glossCount(0), _formOfCount(0)
{
}

//===========================================================================
void LanguageStatistic::visit(const QList<const Node*> &nodes)
{
  ++_entryCount;
  bool unprocessedPartOfSpeech = false;
  for (int i = 0; i < nodes.count(); ++i)
  {
    const Node *child = nodes.at(i);

    // Check if we reached a new section in this entry.
    if (child->type() == Node::Heading)
    {
      const HeadingNode *heading = (const HeadingNode*)child;
      unprocessedPartOfSpeech = (heading->headingType() == Heading::PartOfSpeech);
    }

    if (!unprocessedPartOfSpeech) continue;
    if (child->type() != Node::NumberedList) continue;
    unprocessedPartOfSpeech = false;

    QList<const ListItemNode*> items;
    child->findChildren(items, false);

    // TODO: some of them are form-of.
    _glossCount += items.count();
  }
}
