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
#ifndef WIKT_WEB_VIEW_H
#define WIKT_WEB_VIEW_H

#include <QWebView>

class WebView : public QWebView
{
  Q_OBJECT
public:
  WebView(QWidget *parent);
  /// Returns the HTML content for inspection.
  QString toHtml() const;
  /// Navigates the view to display #id.
  void navigateToId(const QString &id);

signals:
  /// Emitted when the user clicks to a link.
  void localLinkClickedInView(const QUrl &url);

private slots:
  void onUnsupportedContent(QNetworkReply *reply);
  void onDownloadRequested(const QNetworkRequest &request);
  void onLinkClicked(const QUrl &url) { emit localLinkClickedInView(url); }
  void onLoadFinished(bool ok);
};

#endif
