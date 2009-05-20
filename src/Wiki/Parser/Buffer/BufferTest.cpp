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
#include "BufferTest.h"
#include "Buffer.h"
#include <QTest>

//===========================================================================
void BufferTest::read()
{
  // Test reading 0 bytes.
  Buffer buffer("alfa beta");
  QCOMPARE(buffer.read(0), QString(""));
  QCOMPARE(buffer.pos(), 0);
}

//===========================================================================
void BufferTest::readAll()
{
}

//===========================================================================
void BufferTest::nextLine()
{
  Buffer buffer("* a\n* b\n* c\n");
  QCOMPARE(buffer.nextLine(), QString("* a"));
}

//===========================================================================
void BufferTest::readLine()
{
  Buffer buffer("* a\n* b\n* c\n");
  QCOMPARE(buffer.readLine(), QString("* a"));
  QCOMPARE(buffer.readLine(), QString("* b"));
  QCOMPARE(buffer.readLine(), QString("* c"));
}

