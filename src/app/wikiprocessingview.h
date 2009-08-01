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
#ifndef WIKT_WIKI_PROCESSING_VIEW_H
#define WIKT_WIKI_PROCESSING_VIEW_H

#include <QDockWidget>

QT_BEGIN_NAMESPACE
class QTextEdit;
class QPushButton;
QT_END_NAMESPACE

class WikiProcessingView : public QDockWidget
{
  Q_OBJECT
public:
  WikiProcessingView();

private slots:
  void onXmlButtonClicked();

private:
  QPushButton *_xmlButton;
  QTextEdit *_wikiSource;
  QTextEdit *_result;
};

#endif
