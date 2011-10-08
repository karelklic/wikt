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
#include "debug.h"
#include <QTextStream>

void cstdout(const QString &message)
{
  QTextStream ts(stdout);
  ts << message << endl;
}

void _dstdout(const QString &message, const char *file, int line, const char *func)
{
  QTextStream ts(stdout);
  ts << file << ":" << line << " (" << func << ")#" << message << endl;
}

void cstderr(const QString &message)
{
  QTextStream ts(stderr);
  ts << message << endl;
}

void _dstderr(const QString &message, const char *file, int line, const char *func)
{
  QTextStream ts(stderr);
  ts << file << ":" << line << " (" << func << ")#" << message << endl;
}
