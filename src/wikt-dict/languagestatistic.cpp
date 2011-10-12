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
/* This file is required by commandMidToDict. */
#include "languagestatistic.h"
#include <libwikt/tree/headingnode.h>
#include <libwikt/tree/listitemnode.h>

LanguageStatistic::LanguageStatistic() : _entryCount(0), _glossCount(0), _formOfCount(0)
{
}

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

    foreach(const ListItemNode *node, items)
    {
      const QString text = node->toText();
      // The form-of detection strings are gathered from various words in Wiktionary.
      // [[Category:Form_of_templates]] contains various form-of templates.
      bool formOf = 
	text.contains("abessive of", Qt::CaseInsensitive) ||
	text.contains("alternate of", Qt::CaseInsensitive) ||
	text.contains("alternative name of", Qt::CaseInsensitive) ||
	text.contains("alternative spelling of", Qt::CaseInsensitive) ||
	text.contains("alternative captialization of", Qt::CaseInsensitive) ||
	text.contains("compound of", Qt::CaseInsensitive) ||
	text.contains("conditional of", Qt::CaseInsensitive) ||
	text.contains("contraction of", Qt::CaseInsensitive) ||
	text.contains("diminutive of", Qt::CaseInsensitive) ||
	text.contains("dual of", Qt::CaseInsensitive) ||
	text.contains("elative of", Qt::CaseInsensitive) ||
	text.contains("feminine of", Qt::CaseInsensitive) || 
	text.contains("form of", Qt::CaseInsensitive) || 
	text.contains("form? of", Qt::CaseInsensitive) || // Template:hanja form of
	text.contains("future of", Qt::CaseInsensitive) ||
	text.contains("gerund of", Qt::CaseInsensitive) ||
	text.contains("historic of", Qt::CaseInsensitive) ||
	text.contains("illative of", Qt::CaseInsensitive) ||
	text.contains("imperative of", Qt::CaseInsensitive) ||
	text.contains("imperfect of", Qt::CaseInsensitive) ||
	text.contains("indicative of", Qt::CaseInsensitive) ||
	text.contains("inessive of", Qt::CaseInsensitive) ||
	text.contains("infinitive of", Qt::CaseInsensitive) ||
	text.contains("instructive of", Qt::CaseInsensitive) ||
	text.contains("misconstruction of", Qt::CaseInsensitive) ||
	text.contains("misspelling of", Qt::CaseInsensitive) ||
	text.contains("participle of", Qt::CaseInsensitive) || 
	text.contains("past of", Qt::CaseInsensitive) || 
	text.contains("plural of", Qt::CaseInsensitive) ||
	text.contains("present of", Qt::CaseInsensitive) ||
	text.contains("scanno of", Qt::CaseInsensitive) ||
	text.contains("singular of", Qt::CaseInsensitive) ||
	text.contains("spelling of", Qt::CaseInsensitive) ||
	text.contains("subjunctive of", Qt::CaseInsensitive) ||
	text.contains("superlative of", Qt::CaseInsensitive) ||
	text.contains("tense of", Qt::CaseInsensitive);
      formOf ? ++_formOfCount : ++_glossCount;
    }
  }
}
