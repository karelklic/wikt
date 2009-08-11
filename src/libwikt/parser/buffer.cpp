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
#include "buffer.h"
#include "debug.h"

//===========================================================================
Buffer::Buffer() : _pos(0)
{
}

//===========================================================================
Buffer::Buffer(const QString &text, int pos) : _text(text), _pos(pos)
{

}

//===========================================================================
QString Buffer::nextLine() const
{
  CHECK(!endOfFile());
  int offset = _text.indexOf('\n', _pos);
  if (offset == -1)
    return _text.mid(_pos);

  return _text.mid(_pos, offset - _pos);
}

//===========================================================================
QString Buffer::readLine()
{
  QString line = nextLine();
  skip(line.length() + 1); // 1 == newline character
  return line;
}

//===========================================================================
QString Buffer::readAll()
{
  QString rest = _text.mid(_pos);
  _pos = _text.length();
  return rest;
}

//===========================================================================
QString Buffer::read(int count)
{
  QString result = _text.mid(_pos, count);
  _pos += count;
  return result;
}

//===========================================================================
void Buffer::skipEmptyLines()
{
  // Nothing to be skipped when we reached the end.
  if (endOfFile()) return;

  QString line = nextLine();
  if (line.trimmed().length() == 0)
  {
    skip(line.length() + 1);
    skipEmptyLines();
  }
}

//===========================================================================
bool Buffer::startsWith(const QString &text) const
{
  // Check if our buffer is long enough.
  if (_pos + text.length() > _text.length())
    return false;

  for (int i = 0; i < text.length(); ++i)
  {
    if (_text[_pos + i] != text[i])
      return false;
  }

  return true;
}

//===========================================================================
int Buffer::indexOf(const QString &text, Qt::CaseSensitivity cs) const
{
  return _text.indexOf(text, _pos, cs);
}
