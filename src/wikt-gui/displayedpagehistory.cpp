/* This file is part of Wikt. -*- mode: c++; c-file-style: "wikt"; -*-
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
#include "displayedpagehistory.h"

DisplayedPageHistory::DisplayedPageHistory() : _currentItemOffset(-1)
{
}

bool DisplayedPageHistory::canGoBack() const
{
  return _currentItemOffset > 0;
}

bool DisplayedPageHistory::canGoForward() const
{
  return (_items.count() > 1) && _currentItemOffset < (_items.count() - 1);
}

void DisplayedPageHistory::back()
{
  if (_currentItemOffset <= 0) return;

  if (current().scheme() == "notfound")
    _items.removeAt(_currentItemOffset);

  --_currentItemOffset;
  emit changed();
}

void DisplayedPageHistory::forward()
{
  if (_currentItemOffset >= (_items.count() - 1)) return;

  if (current().scheme() == "notfound")
    _items.removeAt(_currentItemOffset);
  else
    ++_currentItemOffset;

  emit changed();
}

void DisplayedPageHistory::addCurrentPage(const QUrl &url)
{
  // If the page to be added is also current page, do not add it.
  if (_currentItemOffset >= 0 && current() == url)
    return;

  if (_currentItemOffset >= 0 && current().scheme() == "notfound")
  {
    _items.removeAt(_currentItemOffset);
    --_currentItemOffset;
  }

  // If we can go forward, remove all forward pages.
  if (_currentItemOffset < _items.count() - 1)
    _items.erase(_items.begin() + _currentItemOffset + 1, _items.end());

  _items.append(url);
  ++_currentItemOffset;
  emit changed();
}
