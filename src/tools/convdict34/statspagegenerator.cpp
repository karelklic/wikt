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
#include "statspagegenerator.h"
#include "format4writer.h"
#include <libwikt/parser/articleparser.h>
#include <libwikt/tree/headingnode.h>
#include <libwikt/debug.h>

//===========================================================================
void StatsPageGenerator::visit(const QString &name, const QString &contents)
{
  // Skip pages with a namespace.
  if (name.contains(':')) return;

  ArticleNode *node = ArticleParser::parse(name, contents);
  Language::Type lang = Language::Unknown;
  QList<const Node*> langNodes;
  for (int i = 0; i < node->count(); ++i)
  {
    const Node *child = node->child(i);

    // Check if we reached a new language section in this entry.
    if (child->type() == Node::Heading)
    {
      const HeadingNode *heading = (const HeadingNode*)child;
      if (heading->level() == 2)
      {
        Language::Type oldLang = lang;
        lang = Language::instance().fromName(heading->toText());

        // Report to console if we found unknown language.
        if (lang == Language::Unknown)
	  cstdout(QString("Unknown language %1 in entry %2").arg(heading->toText()).arg(name));

        // Add language-specific nodes to statistics.
        if (oldLang != Language::Unknown)
        {
          LanguageStatistic &stat = _stats[oldLang];
          stat.visit(langNodes);
        }

        langNodes.clear();
        continue;
      }
    }

    langNodes.append(child);
  }

  // Handle the opened language statistics.
  if (lang != Language::Unknown)
  {
    LanguageStatistic &stat = _stats[lang];
    stat.visit(langNodes);
  }

  delete node;
}

//===========================================================================
void StatsPageGenerator::write(Format4Writer &destination)
{
  QString contents =
    "{| class=\"sortable prettytable\"\n"
    "! Language name || Number of entries || Number of definitions || Gloss definitions || Form-of definitions\n"
    "|-\n";

  for (QMap<Language::Type, LanguageStatistic>::const_iterator it = _stats.constBegin(); it != _stats.constEnd(); ++it)
  {
    contents += QString("! %1\n| %2 || %3 || %4 || %5\n|-\n")
      .arg(Language::instance().toNames(it.key()).first())
      .arg(it.value().entryCount())
      .arg(it.value().definitionCount())
      .arg(it.value().glossCount())
      .arg(it.value().formOfCount());
  }

  contents += "|}\n";
  destination.addEntry("Wikt:Statistics", contents);
}
