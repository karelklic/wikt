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
#include "urlutilstest.h"

void UrlUtilsTest::test0()
{
  QUrl url(UrlUtils::toUrl("machine"));
  QCOMPARE(UrlUtils::toEntryName(url), QString("machine"));
}

void UrlUtilsTest::test1()
{
  QUrl url(UrlUtils::toUrl(QString::fromStdWString(L"MěščřE:Category01 g")));
  QCOMPARE(UrlUtils::toEntryName(url),
      QString(QString::fromStdWString(L"MěščřE:Category01 g")));
}

QTEST_APPLESS_MAIN(UrlUtilsTest)
