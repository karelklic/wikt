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
#include "namespace.h"

const Namespace &Namespace::instance()
{
  static Namespace instance;
  return instance;
}

bool Namespace::isPrefix(const QString &text) const
{
  return _prefixToNamespace.contains(text.toLower());
}

Namespace::Type Namespace::fromPrefix(const QString &prefix) const
{
  return _prefixToNamespace.value(prefix.toLower(), Main);
}

Namespace::Type Namespace::fromCode(const QString &code) const
{
  return _codeToNamespace.value(code.toUpper(), Unknown);
}

Namespace::Type Namespace::fromEntry(const QString &name) const
{
  QStringList prefixes = name.split(':');
  prefixes.removeLast();
  for (int i = 0; i < prefixes.size(); ++i)
    prefixes[i] = prefixes[i].trimmed();
  return fromLinkPrefixes(prefixes);
}

Namespace::Type Namespace::fromLinkPrefixes(const QStringList &prefixes) const
{
  foreach(QString name, prefixes)
  {
    name = name.toLower();
    if (_prefixToNamespace.contains(name))
      return _prefixToNamespace.value(name);
  }

  return Main;
}

QString Namespace::toLocalizedName(Namespace::Type ns) const
{
  return _namespaceToName.value(ns, "");
}

Namespace::Namespace()
{
  _codeToNamespace.insert("-2",    Media);
  _codeToNamespace.insert("MEDIA", Media);
  _codeToNamespace.insert("-1",      Special);
  _codeToNamespace.insert("SPECIAL", Special);
  _codeToNamespace.insert("0",    Main);
  _codeToNamespace.insert("MAIN", Main);
  _codeToNamespace.insert("1",    Talk);
  _codeToNamespace.insert("TALK", Talk);
  _codeToNamespace.insert("2",    User);
  _codeToNamespace.insert("USER", User);
  _codeToNamespace.insert("3",         UserTalk);
  _codeToNamespace.insert("USER_TALK", UserTalk);
  _codeToNamespace.insert("USER TALK", UserTalk);
  _codeToNamespace.insert("4",       Wiktionary);
  _codeToNamespace.insert("PROJECT", Wiktionary);
  _codeToNamespace.insert("5",            WiktionaryTalk);
  _codeToNamespace.insert("PROJECT_TALK", WiktionaryTalk);
  _codeToNamespace.insert("PROJECT TALK", WiktionaryTalk);
  _codeToNamespace.insert("6",     Image);
  _codeToNamespace.insert("IMAGE", Image);
  _codeToNamespace.insert("7",          ImageTalk);
  _codeToNamespace.insert("IMAGE_TALK", ImageTalk);
  _codeToNamespace.insert("IMAGE TALK", ImageTalk);
  _codeToNamespace.insert("8",         MediaWiki);
  _codeToNamespace.insert("MEDIAWIKI", MediaWiki);
  _codeToNamespace.insert("9",              MediaWikiTalk);
  _codeToNamespace.insert("MEDIAWIKI_TALK", MediaWikiTalk);
  _codeToNamespace.insert("MEDIAWIKI TALK", MediaWikiTalk);
  _codeToNamespace.insert("10",       Template);
  _codeToNamespace.insert("TEMPLATE", Template);
  _codeToNamespace.insert("11",            TemplateTalk);
  _codeToNamespace.insert("TEMPLATE_TALK", TemplateTalk);
  _codeToNamespace.insert("TEMPLATE TALK", TemplateTalk);
  _codeToNamespace.insert("12",   Help);
  _codeToNamespace.insert("HELP", Help);
  _codeToNamespace.insert("13",        HelpTalk);
  _codeToNamespace.insert("HELP_TALK", HelpTalk);
  _codeToNamespace.insert("HELP TALK", HelpTalk);
  _codeToNamespace.insert("14",       Category);
  _codeToNamespace.insert("CATEGORY", Category);
  _codeToNamespace.insert("15",            CategoryTalk);
  _codeToNamespace.insert("CATEGORY_TALK", CategoryTalk);
  _codeToNamespace.insert("CATEGORY TALK", CategoryTalk);
  _codeToNamespace.insert("FILE", File);
  _codeToNamespace.insert("FILE_TALK", FileTalk);
  _codeToNamespace.insert("FILE TALK", FileTalk);
  _codeToNamespace.insert("100", Appendix);
  _codeToNamespace.insert("101", AppendixTalk);
  _codeToNamespace.insert("102", Concordance);
  _codeToNamespace.insert("103", ConcordanceTalk);
  _codeToNamespace.insert("104", Index);
  _codeToNamespace.insert("105", IndexTalk);
  _codeToNamespace.insert("106", Rhymes);
  _codeToNamespace.insert("107", RhymesTalk);
  _codeToNamespace.insert("108", Transwiki);
  _codeToNamespace.insert("109", TranswikiTalk);
  _codeToNamespace.insert("110", Wikisaurus);
  _codeToNamespace.insert("111", WikisaurusTalk);
  _codeToNamespace.insert("112", WT);
  _codeToNamespace.insert("113", WTTalk);
  _codeToNamespace.insert("114", Citations);
  _codeToNamespace.insert("115", CitationsTalk);

  _namespaceToName.insert(Media, "Media");
  _namespaceToName.insert(Special, "Special");
  _namespaceToName.insert(Main, "");
  _namespaceToName.insert(Talk, "Talk");
  _namespaceToName.insert(User, "User");
  _namespaceToName.insert(UserTalk, "User talk");
  _namespaceToName.insert(Wiktionary, "Wiktionary");
  _namespaceToName.insert(WiktionaryTalk, "Wiktionary talk");
  _namespaceToName.insert(Wikipedia, "Wikipedia");
  _namespaceToName.insert(WikipediaTalk, "Wikipedia talk");
  _namespaceToName.insert(Image, "Image");
  _namespaceToName.insert(ImageTalk, "Image talk");
  _namespaceToName.insert(MediaWiki, "MediaWiki");
  _namespaceToName.insert(MediaWikiTalk, "MediaWiki talk");
  _namespaceToName.insert(Template, "Template");
  _namespaceToName.insert(TemplateTalk, "Template talk");
  _namespaceToName.insert(Help, "Help");
  _namespaceToName.insert(HelpTalk, "Help talk");
  _namespaceToName.insert(Category, "Category");
  _namespaceToName.insert(CategoryTalk, "Category talk");
  _namespaceToName.insert(File, "File");
  _namespaceToName.insert(FileTalk, "File talk");
  _namespaceToName.insert(Appendix, "Appendix");
  _namespaceToName.insert(AppendixTalk, "Appendix talk");
  _namespaceToName.insert(Concordance, "Concordance");
  _namespaceToName.insert(ConcordanceTalk, "Concordance talk");
  _namespaceToName.insert(Index, "Index");
  _namespaceToName.insert(IndexTalk, "Index talk");
  _namespaceToName.insert(Rhymes, "Rhymes");
  _namespaceToName.insert(RhymesTalk, "Rhymes talk");
  _namespaceToName.insert(Transwiki, "Transwiki");
  _namespaceToName.insert(TranswikiTalk, "Transwiki talk");
  _namespaceToName.insert(Wikisaurus, "Wikisaurus");
  _namespaceToName.insert(WikisaurusTalk, "Wikisaurus talk");
  _namespaceToName.insert(WT, "WT");
  _namespaceToName.insert(WTTalk, "WT talk");
  _namespaceToName.insert(Citations, "Citations");
  _namespaceToName.insert(CitationsTalk, "Citations talk");
  _namespaceToName.insert(Unknown, "");

  _prefixToNamespace.insert("media", Media);
  _prefixToNamespace.insert("special", Special);
  _prefixToNamespace.insert("talk", Talk);
  _prefixToNamespace.insert("user", User);
  _prefixToNamespace.insert("user talk", UserTalk);
  _prefixToNamespace.insert("wiktionary", Wiktionary);
  _prefixToNamespace.insert("wiktionary talk", WiktionaryTalk);
  _prefixToNamespace.insert("wikipedia", Wikipedia);
  _prefixToNamespace.insert("wikipedia talk", WikipediaTalk);
  _prefixToNamespace.insert("image", Image);
  _prefixToNamespace.insert("image talk", ImageTalk);
  _prefixToNamespace.insert("mediawiki", MediaWiki);
  _prefixToNamespace.insert("mediawiki talk", MediaWikiTalk);
  _prefixToNamespace.insert("template", Template);
  _prefixToNamespace.insert("template talk", TemplateTalk);
  _prefixToNamespace.insert("help", Help);
  _prefixToNamespace.insert("help talk", HelpTalk);
  _prefixToNamespace.insert("category", Category);
  _prefixToNamespace.insert("category talk", CategoryTalk);
  _prefixToNamespace.insert("file", File);
  _prefixToNamespace.insert("file talk", FileTalk);
  _prefixToNamespace.insert("appendix", Appendix);
  _prefixToNamespace.insert("appendix talk", AppendixTalk);
  _prefixToNamespace.insert("concordance", Concordance);
  _prefixToNamespace.insert("concordance talk", ConcordanceTalk);
  _prefixToNamespace.insert("index", Index);
  _prefixToNamespace.insert("index talk", IndexTalk);
  _prefixToNamespace.insert("rhymes", Rhymes);
  _prefixToNamespace.insert("rhymes talk", RhymesTalk);
  _prefixToNamespace.insert("transwiki", Transwiki);
  _prefixToNamespace.insert("transwiki talk", TranswikiTalk);
  _prefixToNamespace.insert("wikisaurus", Wikisaurus);
  _prefixToNamespace.insert("wikisaurus talk", WikisaurusTalk);
  _prefixToNamespace.insert("wt", WT);
  _prefixToNamespace.insert("wt talk", WTTalk);
  _prefixToNamespace.insert("citations", Citations);
  _prefixToNamespace.insert("citations talk", CitationsTalk);
}
