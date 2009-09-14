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
#include "unicode.h"
#include <sstream>
#include <iomanip>

//===========================================================================
std::string Unicode::escape(const QString &contents)
{
  std::stringstream ss;
  const QChar *data = contents.data();
  while (!data->isNull())
  {
    if (data->unicode() == 'x')
      ss << "xx";
    else if (data->unicode() <= 127)
      ss << (char)data->unicode();
    else
    {
      ss << "x" << std::setw(4) << std::right << std::setfill('0') <<
        std::setbase(16) << data->unicode();
    }
    ++data;
  }

  return ss.str();
}

//===========================================================================
QString Unicode::unescape(const std::string &contents)
{
  QString result;
  result.reserve(contents.size());
  for (unsigned i = 0; i < contents.size(); ++i)
  {
    if (contents[i] != 'x')
      result.append(QChar(contents[i]));
    else
    {
      ++i;
      if (contents[i] == 'x')
        result.append(QChar(contents[i]));
      else
      {
        QString num = QString::fromStdString(contents.substr(i, 4));
        QChar c(num.toUInt(0, 16));
        result.append(c);
        i += 3;
      }
    }
  }
  return result;
}

//===========================================================================
QString Unicode::unescape(const QString &contents)
{
  QString result;
  result.reserve(contents.size());
  for (int i = 0; i < contents.size(); ++i)
  {
    if (contents[i] != 'x')
      result.append(QChar(contents[i]));
    else
    {
      ++i;
      if (contents[i] == 'x')
        result.append(QChar(contents[i]));
      else
      {
        QString num = contents.mid(i, 4);
        QChar c(num.toUInt(0, 16));
        result.append(c);
        i += 3;
      }
    }
  }
  return result;
}

//===========================================================================
static inline uint foldCase(uint ch, uint &last)
{
    uint c = ch;
    if (QChar(c).isLowSurrogate() && QChar(last).isHighSurrogate())
        c = QChar::surrogateToUcs4(last, c);
    last = ch;
    return QChar::toCaseFolded(c);
}

//===========================================================================
int Unicode::ucstricmp(const ushort *a, const ushort *ae, const ushort *b, const ushort *be)
{
    if (a == b)
        return 0;
    if (a == 0)
        return 1;
    if (b == 0)
        return -1;

    const ushort *e = ae;
    if (be - b < ae - a)
        e = a + (be - b);

    uint alast = 0;
    uint blast = 0;
    while (a != e) {
        int diff = foldCase(*a, alast) - foldCase(*b, blast);
        if ((diff))
            return diff;
        ++a;
        ++b;
    }
    if (a == ae) {
        if (b == be)
            return 0;
        return -1;
    }
    return 1;
}
