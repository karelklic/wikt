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
#include "WebView.h"
#include "NetworkAccessManager.h"
#include "../MainWindow.h"
#include "../LookupPanel.h"
#include <libwikt/UrlUtils.h>
#include <libwikt/Prerequisites.h>
#include <QWebFrame>
#include <QNetworkReply>
#include <QFile>
#include <QSettings>

//===========================================================================
WebView::WebView(QWidget *parent) : QWebView(parent)
{
  connect(page(), SIGNAL(unsupportedContent(QNetworkReply*)),
          this, SLOT(onUnsupportedContent(QNetworkReply*)));
  connect(page(), SIGNAL(linkClicked(const QUrl&)),
          this, SLOT(onLinkClicked(const QUrl&)));
  connect(page(), SIGNAL(downloadRequested(const QNetworkRequest&)),
          this, SLOT(onDownloadRequested(const QNetworkRequest&)));
  connect(this, SIGNAL(loadFinished(bool)),
          this, SLOT(onLoadFinished(bool)));
  page()->setForwardUnsupportedContent(true);
  page()->setNetworkAccessManager(new NetworkAccessManager(this));
  page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
  show();
}

//===========================================================================
QString WebView::toHtml() const
{
  return page()->mainFrame()->toHtml();
}

//===========================================================================
void WebView::navigateToId(const QString &id)
{
  QString code = QString("window.location.hash=\"%1\";").arg(id);
  page()->mainFrame()->evaluateJavaScript(code);
}

//===========================================================================
void WebView::onUnsupportedContent(QNetworkReply */*reply*/)
{
  MSG("onUnsupportedContent not supported yet.");
}

//===========================================================================
void WebView::onDownloadRequested(const QNetworkRequest &/*request*/)
{
  MSG("onDownloadRequest not supported yet.");
}

//===========================================================================
void WebView::onLoadFinished(bool ok)
{
  if (!ok) return;

  QSettings settings;
  bool translationsFolded = settings.value("translationsFolded", true).toBool();

  QString sectionId;
  UrlUtils::toEntryName(url(), &sectionId);
  if (sectionId.length() > 0)
    navigateToId(sectionId);
}
