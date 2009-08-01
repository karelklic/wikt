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
#include "networkreplystylesheet.h"
#include <QTimer>

//===========================================================================
NetworkReplyStylesheet::NetworkReplyStylesheet(const QNetworkRequest &request,
    QObject *parent) : QNetworkReply(parent)
{
  QString css;
  css += "body { margin:0; padding:0 1em 1em 0.6em; }";
  css += "h1, h2, h3, h4, h5, h6 { margin:0; padding-top:.5em; padding-bottom:.17em; overflow:hidden; width:auto;}";
  css += "h1 { font-size:188%; border-bottom:1px solid #aaa; }";
  css += "h2 { font-size:150%; border-bottom:1px solid #aaa; }";
  css += "h3 { font-size:132%; }";
  css += "h4 { font-size:116%; }";
  css += "h5 { font-size:100%; }";
  css += "h6 { font-size:80%; }";
  css += "b { font-weight:600; }";
  css += "hr { height:1px; color:#aaa; background-color:#aaa; border:0; margin:.2em 0 .2em 0; }";
  css += "p { margin:.4em 0 .5em 0; line-height:1.3em; }";
  css += "a { text-decoration:none; color:#002bb8; background:none; }";
  css += "a { text-decoration:none; color:#002bb8; background:none; }";
  css += "a:visited { color:#5a3696; }";
  css += "a:active { color: #faa700; }";
  css += "a:hover { text-decoration:underline; }";
  css += "ul { line-height:1.5em; list-style-type:square; margin:.3em 0 0 1.5em; padding:0; list-style-image:url(\"embedded://images/bullet.gif\") }";
  css += "ol { line-height:1.5em; margin:.3em 0 0 3.2em; padding:0; list-style-image: none; }";
  css += "li { margin-bottom:.1em; }";
  css += "dt { font-weight:bold; margin-bottom:.1em; }";
  css += "dl { margin-top:.2em; margin-bottom:.5em; }";
  css += "dd { line-height:1.5em; margin-left:2em; margin-bottom:.1em; }";
  css += "div.floatright, table.floatright { clear:right; float:right; position:relative; margin:0 0 .5em .5em; border:0; }";
  css += "div.floatright p { font-style:italic; }";
  css += "div.floatleft, table.floatleft { float:left; clear:left; position:relative; margin:0 .5em .5em 0; border:0; }";
  css += "div.floatleft p { font-style:italic; }\n";
  // images
  /* thumbnails */
  css += "div.thumb { margin-bottom: .5em; border-style: solid; border-color: white; width: auto; }";
  css += "div.thumbinner { border: 1px solid #ccc; padding: 3px !important; background-color: #f9f9f9; font-size: 94%; text-align: center; overflow: hidden; }";
  css += "html .thumbimage { border: 1px solid #ccc; }";
  css += "html .thumbcaption { border: none; text-align: left; line-height: 1.4em; padding: 3px !important; font-size: 94%; }";
  css += "div.magnify { float: right; border: none !important; background: none !important; }";
  css += "div.magnify a, div.magnify img { display: block; border: none !important; background: none !important; }";
  css += "div.tright { clear: right; float: right; border-width: .5em 0 .8em 1.4em; }";
  css += "div.tleft { float: left; clear: left; margin-right: .5em; border-width: .5em 1.4em .8em 0; }";
  css += "img.thumbborder { border: 1px solid #dddddd; }";
  // iwiki
  css += ".interProject { display:none; clear:both; border-top:2px dotted #AAAAAA; margin-top:2em; }\n";
  css += ".ib-comma { font-style:normal }\n";
  css += ".ib-content { font-style:italic }\n";
  css += ".context-qualifier-colon { display:none }\n";
  css += ".infl-inline { display:inline }\n";
  css += ".infl-table { display:none }\n";
  // default style for mentions outside of "form of" definitions per [[Wiktionary:Votes/2007-10/style for mentioned terms]]
  css += ".mention { font-style:italic }";
  css += ".mention-Latn { font-style:italic }";
  css += ".mention-gloss-single-quote { display:none }";
  css += ".mention-tr-gloss-separator-paren { display:none }";
  css += ".mention-tr { font-style:italic }";
  // default style for "form of" definitions
  css += ".use-with-mention .mention, .defn-form-of .lemma { font-style: normal; font-weight: bold; }";
  // pretty tables
  css += "table.wikitable, table.prettytable { margin:1em 1em 1em 0; background:#f9f9f9; border:1px #aaaaaa solid; border-collapse:collapse; }";
  css += "table.wikitable th, table.wikitable td, table.prettytable th, table.prettytable td { border: 1px #aaaaaa solid; padding: 0.2em; }";
  css += "table.wikitable th, table.prettytable th { background: #f2f2f2; text-align: center; }";
  css += "table.wikitable caption, table.prettytable caption { margin-left: inherit; margin-right: inherit; }";
  // SVG images are not supported in current version of WebKit.
  css += ".audiolink a { background:url(\"embedded://images/loudspeaker.png\") center left no-repeat !important; padding-left:20px !important; padding-right: 0 !important; }";
  css += ".IPA { font-size:110%; }";
  // Toggable tables.
  css += "div.NavFrame { margin:0; padding:2px; border:1px solid #aaa; text-align:center; border-collapse:collapse; font-size:95%; overflow:auto; width:auto; }";
  css += "div.NavFrame+div.NavFrame{border-top-style:none;border-top-style:hidden}";
  css += "div.NavFrame div.NavHead { font-weight:bold; background-color:#efefef; padding:2px 0.5ex 2px 0.4ex; margin:0; }";
  css += "span.NavToggle{ float:right; font-weight:normal; font-size:smaller; cursor:pointer }";
  css += "div.NavEnd { margin: 0px; padding: 0px; line-height: 1px; clear: both; }";
  // hide the serial commas and gender abbreviation periods
  css += ".serial-comma, .gender-period { display: none }";
  // Translations table
  css += ".checktrans { background-color: #f0fff0 }";
  css += ".rfc-trans { background-color: #f0fff0 }";
  css += ".trreq { background-color: #f0fff0 }";
  css += ".ttbc { background-color: #f0fff0 }";
  css += ".tneg, .tpos, .tunk { vertical-align: 20%; font-size: 80%; }";
  css += ".tlc  { display: none }";

  _buffer.open(QBuffer::ReadWrite);
  _buffer.write(css.toUtf8());
  _buffer.seek(0);

  setRequest(request);
  setUrl(request.url());
  setOpenMode(QIODevice::ReadOnly);
  setOperation(QNetworkAccessManager::GetOperation);
  setHeader(QNetworkRequest::ContentTypeHeader, "text/css;charset=utf-8");
  setHeader(QNetworkRequest::ContentLengthHeader, _buffer.size());

  QTimer::singleShot(0, this, SIGNAL(metaDataChanged()));
  QTimer::singleShot(0, this, SIGNAL(readyRead()));

  connect(&_checkFinishedTimer, SIGNAL(timeout()),
      this, SLOT(checkFinished()));
  _checkFinishedTimer.start(50);
}

//===========================================================================
void NetworkReplyStylesheet::checkFinished()
{
  if (_buffer.bytesAvailable() + QNetworkReply::bytesAvailable() == 0)
  {
    _checkFinishedTimer.stop();
    QTimer::singleShot(0, this, SIGNAL(finished()));
  }
}
