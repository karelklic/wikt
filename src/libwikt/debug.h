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
#ifndef LIBWIKT_DEBUG_H_
#define LIBWIKT_DEBUG_H_

#include <QString>

/// Adds a debug message to console output.
#define dstdout(msg) _dstdout(msg, __FILE__, __LINE__, __FUNCTION__)

/// Adds a debug message to console error output.
#define dstderr(msg) _dstderr(msg, __FILE__, __LINE__, __FUNCTION__)

#define CHECK(__expr) {if (!(__expr)) { dstderr((#__expr)); }}
#define CHECK_MSG(__expr, __msg) { if (!(__expr)) { dstderr(QString("%1 (expr: %2)").arg(__msg, #__expr)); }}

/// Writes the message to the stdout.
void cstdout(const QString &message);
/// Writes the message to the stdout together with the source file, line and function.
void _dstdout(const QString &message, const char *file, int line, const char *func);

/// Writes the message to the stderr.
void cstderr(const QString &message);
/// Writes the message to the stderr together with the source file, line and function.
void _dstderr(const QString &message, const char *file, int line, const char *func);

#endif /* LIBWIKT_DEBUG_H_ */
