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
#ifndef DISPLAYEDPAGEHISTORY_H_
#define DISPLAYEDPAGEHISTORY_H_

#include <QObject>
#include <QList>
#include <QUrl>

/// Stores a list of previously displayed pages.
/// Allows browsing the history by moving backward and then forward.
class DisplayedPageHistory : public QObject
{
  Q_OBJECT
public:
  /// Standard constructor.
  DisplayedPageHistory();

  bool canGoBack() const;
  bool canGoForward() const;

  void back();
  void forward();

  const QUrl &current() const { return _items[_currentItemOffset]; }

  void addCurrentPage(const QUrl &url);

signals:
  void changed();

protected:
  QList<QUrl> _items;
  int _currentItemOffset;
};

#endif /* DISPLAYEDPAGEHISTORY_H_ */
