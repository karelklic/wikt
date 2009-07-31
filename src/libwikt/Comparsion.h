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
#ifndef COMPARSION_H
#define COMPARSION_H

#include "Prerequisites.h"
#include <QString>
#include <QPair>

struct Comparsion
{
  inline bool operator()(const QString &a, const QString &b) const
  {
    return a < b;
  }

  inline bool operator()(const QPair<QString, size_t> &a,
    const QPair<QString, size_t> &b) const
  {
    return operator()(a.first, b.first);
  }
};

#endif

