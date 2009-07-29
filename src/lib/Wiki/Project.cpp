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
#include "Project.h"

//===========================================================================
const Project &Project::instance()
{
  static Project instance;
  return instance;
}

//===========================================================================
bool Project::isProjectPrefix(const QString &prefix) const
{
  return _prefix.contains(prefix.toLower());
}

//===========================================================================
Project::Type Project::fromPrefix(const QString &prefix) const
{
  return _prefix.value(prefix.toLower(), Unknown);
}

//===========================================================================
Project::Type Project::fromLinkPrefixes(const QStringList &prefixes) const
{
  foreach(QString name, prefixes)
  {
    name = name.toLower();
    if (_prefix.contains(name))
      return _prefix.value(name);
  }

  return Wiktionary;
}

//===========================================================================
QString Project::toUrl(Project::Type project, Language::Type language) const
{
  QString url = _url.value(project, "Unknown URL");
  if (url.contains("%1"))
    url = url.arg(Language::instance().toCode(language));

  return url;
}

//===========================================================================
Project::Project()
{
  _prefix.insert("m",           Meta);
  _prefix.insert("meta",        Meta);
  _prefix.insert("w",           Wikipedia);
  _prefix.insert("wikipedia",   Wikipedia);
  _prefix.insert("s",           Wikisource);
  _prefix.insert("wikisource",  Wikisource);
  _prefix.insert("q",           Wikiquote);
  _prefix.insert("wikiquote",   Wikiquote);
  _prefix.insert("b",           Wikibooks);
  _prefix.insert("wikibooks",   Wikibooks);
  _prefix.insert("n",           Wikinews);
  _prefix.insert("wikinews",    Wikinews);
  _prefix.insert("v",           Wikiversity);
  _prefix.insert("wikiversity", Wikiversity);
  _prefix.insert("commons",     Commons);
  _prefix.insert("species",     Wikispecies);
  _prefix.insert("wikispecies", Wikispecies);
  _prefix.insert("wikimedia",   Wikimedia);
  _prefix.insert("mw",          MediaWiki);
  _prefix.insert("mediazilla",  Mediazilla);

  _url.insert(Meta,        "http://meta.wikimedia.org/wiki/");
  _url.insert(Wiktionary,  "http://%1.wiktionary.org/wiki/");
  _url.insert(Wikipedia,   "http://%1.wikipedia.org/wiki/");
  _url.insert(Wikisource,  "http://%1.wikisource.org/wiki/");
  _url.insert(Wikiquote,   "http://%1.wikiquote.org/wiki/");
  _url.insert(Wikibooks,   "http://%1.wikibooks.org/wiki/");
  _url.insert(Wikinews,    "http://%1.wikinews.org/wiki/");
  _url.insert(Wikiversity, "http://%1.wikiversity.org/wiki/");
  _url.insert(Commons,     "http://commons.wikimedia.org/wiki/");
  _url.insert(Wikispecies, "http://species.wikimedia.org/wiki/");
  _url.insert(Wikimedia,   "http://wikimediafoundation.org/wiki/");
  _url.insert(MediaWiki,   "http://www.mediawiki.org/wiki/");
  _url.insert(Mediazilla,  "http://bugzilla.wikimedia.org/");
}
