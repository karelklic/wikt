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
 *
 * Copyright © 2008 the authors from
 * http://en.literateprograms.org/Quicksort_(C_Plus_Plus)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <qalgorithms.h>
#include <QPair>
#include <cstdlib>

template<typename IT, typename LESS_THAN>
IT partition(IT begin, IT end, IT pivot, LESS_THAN lessThan)
{
  typename IT::value_type piv(*pivot);
  qSwap(*pivot, *(end-1));
  IT store = begin;
  for (IT it = begin; it != end - 1; ++it)
  {
    if (lessThan(*it, piv))
    {
      qSwap(*store, *it);
      ++store;
    }
  }

  qSwap(*(end - 1), *store);
  return store;
}

template<typename IT, typename LESS_THAN>
struct pivotMedian
{
  LESS_THAN _lessThan;

  pivotMedian(LESS_THAN lessThan) : _lessThan(lessThan) {}

  IT operator()(IT begin, IT end)
  {
    IT pivot(begin + (end - begin) / 2);
    if (_lessThan(*begin, *pivot) && _lessThan(*(end - 1), *begin))
      pivot = begin;
    else if (_lessThan(*(end - 1), *pivot) && _lessThan(*begin, *(end - 1)))
      pivot = end-1;

    return pivot;
  }
};

template<typename IT>
struct pivotRandom
{
  pivotRandom() { std::srand(time(NULL)); }
  IT operator()(IT begin, IT end) { return begin + (std::rand() % (end - begin)); }
};

template<typename IT, typename PF, typename LESS_THAN>
void quickSort(IT begin, IT end, PF pf, LESS_THAN lessThan)
{
  if (end - begin > 1)
  {
    IT pivot = pf(begin, end);
    pivot = partition(begin, end, pivot, lessThan);
    quickSort(begin, pivot, pf, lessThan);
    quickSort(pivot + 1, end, pf, lessThan);
  }
}

/// qSort from Qt does not work for our huge lists.
/// The pivot is badly chosen in qSort.
template<typename IT, typename LESS_THAN>
void quickSort(IT begin, IT end, LESS_THAN lessThan)
{
  quickSort(begin, end, pivotRandom<IT>(), lessThan);
}

#endif

