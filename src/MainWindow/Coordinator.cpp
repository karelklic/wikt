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
#include "Coordinator.h"
#include "MainWindow.h"
#include "LookupPanel.h"
#include "WebView/WebView.h"
#include "WebView/UrlUtils.h"
#include "../RelatedPages/Panel.h"
#include "../TableOfContents/TocPanel.h"
#include "../Categories/CategoriesPanel.h"
#include "../Wiki/WikiSource.h"
#include "../Media/MediaPlayer.h"
#include "../Wiki/Tree/Article/ArticleNode.h"
#include "../Prerequisites.h"
#include <QAction>
#include <QDesktopServices>

//===========================================================================
Coordinator::Coordinator(QObject *parent) : QObject(parent), _state(Initial)
{
  // Do nothing here, almost no other application object is initialized
  // now.
}

//===========================================================================
void Coordinator::textEnteredToLookup(const QString &text)
{
  // Cache
  if (_state == TextEnteredToLookup && _text == text) return;
  _state = TextEnteredToLookup;
  _text = text;

  // TODO: what if the text is not found.
  //  - try to split it to words
  //  - small/large caps
  //  - display an error page
  MainWindow *window = MainWindow::instance();
  WikiSource *reader = window->wikiSource();
  if (!reader->exist(text))
    return;

  QUrl url(UrlUtils::toUrl(text));
  Node *node = reader->tree(text);

  window->setTitle(text);
  window->webView()->setUrl(url);
  window->lookupPanel()->history().addCurrentPage(url);
  window->tableOfContentsPanel()->model().generateFrom(node);
  window->relatedPagesPanel()->model().generateFrom(text, node);
  window->categoriesPanel()->model().generateFrom(node);
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
    if (!window->wikiSource()->exist(entry))
      return;

    Node *node = window->wikiSource()->tree(entry);
    window->setTitle(entry);
    window->webView()->setUrl(url);
    window->lookupPanel()->history().addCurrentPage(url);
    window->tableOfContentsPanel()->model().generateFrom(node);
    window->relatedPagesPanel()->model().generateFrom(entry, node);
    window->categoriesPanel()->model().generateFrom(node);
  }
  else if (url.scheme() == "media")
    window->mediaPlayer()->play(entry);
  else if (url.scheme() == "http")
    QDesktopServices::openUrl(url);
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
  Node *node = window->wikiSource()->tree(word);

  window->setTitle(word);
  window->webView()->setUrl(url);
  window->lookupPanel()->history().addCurrentPage(url);
  window->tableOfContentsPanel()->model().generateFrom(node);
  window->relatedPagesPanel()->model().partialUpdateFrom(word, node);
  window->categoriesPanel()->model().generateFrom(node);
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
  window->relatedPagesPanel()->model().generateForTitlePage();
  window->tableOfContentsPanel()->model().clear();
  window->categoriesPanel()->model().clear();
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
  QString entry(UrlUtils::toEntryName(url));
  Node *node = window->wikiSource()->tree(entry);
  window->setTitle(entry);
  window->webView()->setUrl(url);
  window->lookupPanel()->history().addCurrentPage(url);
  window->tableOfContentsPanel()->model().generateFrom(node);
  window->relatedPagesPanel()->model().generateFrom(entry, node);
  window->categoriesPanel()->model().generateFrom(node);
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
