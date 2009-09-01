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
#ifndef WIKT_MAIN_WINDOW_H
#define WIKT_MAIN_WINDOW_H

#include <QMainWindow>

class MenuBar;
class WebView;
class Coordinator;
class LookupPanel;
class WikiSource;
class FindPanel;
class MediaPlayer;
namespace RelatedPages { class Panel; }
namespace TableOfContents { class Panel; }
namespace Categories { class Panel; }
namespace InterestingPages { class Panel; }

/// The main application window.
/// Holds links to all window members and important application parts.
class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  /// Standard constructor.
  MainWindow();
  ~MainWindow();
  static MainWindow *instance();

  WebView *webView() const { return _webView; }
  LookupPanel *lookupPanel() const { return _lookupPanel; }
  TableOfContents::Panel *tableOfContentsPanel() const { return _tableOfContentsPanel; }
  RelatedPages::Panel *relatedPagesPanel() const { return _relatedPagesPanel; }
  Categories::Panel *categoriesPanel() const { return _categoriesPanel; }
  InterestingPages::Panel *interestingPagesPanel() const { return _interestingPagesPanel; }
  Coordinator *coordinator() const { return _coordinator; }
  WikiSource *wikiSource() const { return _wikiSource; }
  FindPanel *findPanel() const { return _findPanel; }
  MediaPlayer *mediaPlayer() const { return _mediaPlayer; }

  void setTitle(const QString &text);

private slots:
  void linkHovered(const QString &link, const QString &title, const QString &textContent);

protected:
  /// Override QWidget
  virtual void keyReleaseEvent(QKeyEvent *event);

private:
  MenuBar *_mainMenuBar;
  WebView *_webView;
  LookupPanel *_lookupPanel;
  TableOfContents::Panel *_tableOfContentsPanel;
  RelatedPages::Panel *_relatedPagesPanel;
  Categories::Panel *_categoriesPanel;
  InterestingPages::Panel *_interestingPagesPanel;
  Coordinator *_coordinator;
  WikiSource *_wikiSource;
  FindPanel *_findPanel;
  MediaPlayer *_mediaPlayer;
};

#endif
