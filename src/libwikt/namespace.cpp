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

//===========================================================================
const Namespace &Namespace::instance()
{
  static Namespace instance;
  return instance;
}

//===========================================================================
Namespace::Type Namespace::fromCode(const QString &code) const
{
  return _codeToNamespace.value(code.toUpper(), Unknown);
}

//===========================================================================
Namespace::Type Namespace::fromEntry(const QString &name) const
{
  QStringList prefixes = name.split(':');
  prefixes.removeLast();
  for (int i = 0; i < prefixes.size(); ++i)
    prefixes[i] = prefixes[i].trimmed();
  return fromLinkPrefixes(prefixes);
}

//===========================================================================
Namespace::Type Namespace::fromLinkPrefixes(const QStringList &prefixes) const
{
  foreach(QString name, prefixes)
  {
    name = name.toLower();
    if (_linkToNamespace.contains(name))
      return _linkToNamespace.value(name);
  }

  return Main;
}

//===========================================================================
QString Namespace::toLocalizedName(Namespace::Type ns) const
{
  return _namespaceToName.value(ns, "");
}

//===========================================================================
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

  _linkToNamespace.insert("media", Media);
  _linkToNamespace.insert("special", Special);
  _linkToNamespace.insert("talk", Talk);
  _linkToNamespace.insert("user", User);
  _linkToNamespace.insert("user talk", UserTalk);
  _linkToNamespace.insert("wiktionary", Wiktionary);
  _linkToNamespace.insert("wiktionary talk", WiktionaryTalk);
  _linkToNamespace.insert("wikipedia", Wikipedia);
  _linkToNamespace.insert("wikipedia talk", WikipediaTalk);
  _linkToNamespace.insert("image", Image);
  _linkToNamespace.insert("image talk", ImageTalk);
  _linkToNamespace.insert("mediaWiki", MediaWiki);
  _linkToNamespace.insert("mediaWiki talk", MediaWikiTalk);
  _linkToNamespace.insert("template", Template);
  _linkToNamespace.insert("template talk", TemplateTalk);
  _linkToNamespace.insert("help", Help);
  _linkToNamespace.insert("help talk", HelpTalk);
  _linkToNamespace.insert("category", Category);
  _linkToNamespace.insert("category talk", CategoryTalk);
  _linkToNamespace.insert("file", File);
  _linkToNamespace.insert("file talk", FileTalk);
  _linkToNamespace.insert("appendix", Appendix);
  _linkToNamespace.insert("appendix talk", AppendixTalk);
  _linkToNamespace.insert("concordance", Concordance);
  _linkToNamespace.insert("concordance talk", ConcordanceTalk);
  _linkToNamespace.insert("index", Index);
  _linkToNamespace.insert("index talk", IndexTalk);
  _linkToNamespace.insert("rhymes", Rhymes);
  _linkToNamespace.insert("rhymes talk", RhymesTalk);
  _linkToNamespace.insert("transwiki", Transwiki);
  _linkToNamespace.insert("transwiki talk", TranswikiTalk);
  _linkToNamespace.insert("wikisaurus", Wikisaurus);
  _linkToNamespace.insert("wikisaurus talk", WikisaurusTalk);
  _linkToNamespace.insert("wt", WT);
  _linkToNamespace.insert("wt talk", WTTalk);
  _linkToNamespace.insert("citations", Citations);
  _linkToNamespace.insert("citations talk", CitationsTalk);
}
