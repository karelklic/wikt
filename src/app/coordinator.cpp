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
#include "coordinator.h"
#include "mainwindow.h"
#include "lookuppanel.h"
#include "webview.h"
#include "relpagespanel.h"
#include "tocpanel.h"
#include "categoriespanel.h"
#include "interestingpagespanel.h"
#include "mediaplayer.h"
#include "wikisource.h"
#include <libwikt/urlutils.h>
#include <libwikt/tree/articlenode.h>
#include <QAction>
#include <QDesktopServices>

//===========================================================================
Coordinator::Coordinator(QObject *parent) : QObject(parent), _state(Initial)
{
  // Do nothing here, almost no other application object is initialized
  // now.
}

//===========================================================================
void Coordinator::textEnteredToLookup(QString text)
{
  // Cache
  if (_state == TextEnteredToLookup && _text == text) return;
  _state = TextEnteredToLookup;

  // TODO: what if the text is not found.
  //  - try to split it to words
  //  - small/large caps
  //  - display an error page
  MainWindow *window = MainWindow::instance();
  WikiSource *reader = window->wikiSource();
  QStringList entries;
  if (reader->exist(text))
    entries.append(text);
  else
  {
    text.replace(',', ' ');
    QStringList splitted = text.split(' ', QString::SkipEmptyParts);
    foreach (const QString &s, splitted)
    {
      if (reader->exist(s))
        entries.append(s);
    }
  }

  if (entries.empty())
    return; // todo error page

  _text = entries.first();
  QUrl url(UrlUtils::toUrl(entries.first()));
  QList<const ArticleNode*> nodes;
  foreach (const QString &entry, entries)
    nodes.append(reader->tree(entry));

  window->setTitle(entries.first());
  window->webView()->setUrl(url);
  window->lookupPanel()->history().addCurrentPage(url);
  window->tableOfContentsPanel()->model().generateFrom(nodes.first());
  window->relatedPagesPanel()->model().generateFrom(nodes);
  window->categoriesPanel()->model().generateFrom(*nodes.first());
  window->interestingPagesPanel()->model().generate();
}

//===========================================================================
void Coordinator::localLinkClickedInView(const QUrl &url)
{
  // Cache
  _state = LocalLinkClickedInView;

  MainWindow *window = MainWindow::instance();
  QString entry(UrlUtils::toEntryName(url));

  if (url.scheme() == "entry" || url.scheme() == "special")
  {
    // Do not crash when user clicks a link to nonexisting word.
    if (!window->wikiSource()->exist(entry)) return;
    _text = entry;

    ArticleNode *node = window->wikiSource()->tree(entry);
    window->setTitle(entry);
    window->webView()->setUrl(url);
    window->lookupPanel()->history().addCurrentPage(url);
    window->tableOfContentsPanel()->model().generateFrom(node);
    window->relatedPagesPanel()->model().generateFrom(node);
    window->categoriesPanel()->model().generateFrom(*node);
    window->interestingPagesPanel()->model().generate();
  }
  else if (url.scheme() == "media")
    window->mediaPlayer()->play(entry);
  else if (url.scheme() == "http")
    QDesktopServices::openUrl(url);
}

//===========================================================================
void Coordinator::interestingPagesPanelClicked(const QString &entry)
{
  // Cache
  if (_state == LocalLinkClickedInInterestingPagesPanel && _text == entry) return;
  _state = LocalLinkClickedInInterestingPagesPanel;
  _text = entry;

  MainWindow *window = MainWindow::instance();

  QUrl url(UrlUtils::toUrl(entry));
  ArticleNode *node = window->wikiSource()->tree(entry);

  window->setTitle(entry);
  window->webView()->setUrl(url);
  window->lookupPanel()->history().addCurrentPage(url);
  window->tableOfContentsPanel()->model().generateFrom(node);
  window->relatedPagesPanel()->model().generateFrom(node);
  window->categoriesPanel()->model().generateFrom(*node);
  window->interestingPagesPanel()->model().generate();
}

//===========================================================================
void Coordinator::localLinkClickedInRelatedPagesPanel(const QString &word)
{
  // Cache
  if (_state == LocalLinkClickedInRelatedPagesPanel && _text == word) return;
  _state = LocalLinkClickedInRelatedPagesPanel;
  _text = word;

  MainWindow *window = MainWindow::instance();

  QUrl url(UrlUtils::toUrl(word));
  ArticleNode *node = window->wikiSource()->tree(word);
  if (node == 0) return; // the word does not exist

  window->setTitle(word);
  window->webView()->setUrl(url);
  window->lookupPanel()->history().addCurrentPage(url);
  window->tableOfContentsPanel()->model().generateFrom(node);
  window->relatedPagesPanel()->model().partialUpdateFrom(word, node);
  window->categoriesPanel()->model().generateFrom(*node);
  window->interestingPagesPanel()->model().generate();
}

//===========================================================================
void Coordinator::categoryClickedInCategoriesPanel(const QString &entry)
{
  // Different handling later.
  textEnteredToLookup(entry);
}

//===========================================================================
void Coordinator::tableOfContentsClicked(const QString &headingId)
{
  MainWindow::instance()->webView()->navigateToId(headingId);
}

//===========================================================================
void Coordinator::homeActivated()
{
  // Cache
  if (_state == HomeActivated) return;
  _state = HomeActivated;

  MainWindow *window = MainWindow::instance();
  QUrl url("special://titlepage");
  window->setTitle("");
  window->webView()->setUrl(url);
  window->lookupPanel()->history().addCurrentPage(url);
  window->relatedPagesPanel()->model().clear();
  window->tableOfContentsPanel()->model().clear();
  window->categoriesPanel()->model().clear();
  window->interestingPagesPanel()->model().generate();
}

//===========================================================================
void Coordinator::historyActivated(const QUrl &url)
{
  if (url.scheme() == "special" && url.host() == "titlepage")
  {
    homeActivated();
    return;
  }

  // Cache
  _state = LocalLinkClickedInRelatedPagesPanel;

  MainWindow *window = MainWindow::instance();
  _text = UrlUtils::toEntryName(url);
  ArticleNode *node = window->wikiSource()->tree(_text);
  window->setTitle(_text);
  window->webView()->setUrl(url);
  window->lookupPanel()->history().addCurrentPage(url);
  window->tableOfContentsPanel()->model().generateFrom(node);
  window->relatedPagesPanel()->model().generateFrom(node);
  window->categoriesPanel()->model().generateFrom(*node);
  window->interestingPagesPanel()->model().generate();
}

//===========================================================================
void Coordinator::userSettingChanged_SectionVisibility()
{
  MainWindow *window = MainWindow::instance();
  window->wikiSource()->sectionVisibilityChanged();
  window->webView()->reload();

  QUrl url = window->webView()->url();
  if (url.scheme() == "special" && url.host() == "titlepage")
    return;

  QString entry(UrlUtils::toEntryName(url));
  Node *node = window->wikiSource()->tree(entry);
  window->tableOfContentsPanel()->model().generateFrom(node);
}

//===========================================================================
void Coordinator::userSettingChanged_Translations()
{
  MainWindow *window = MainWindow::instance();
  window->wikiSource()->translationSettingsChanged();
  window->webView()->reload();
}
