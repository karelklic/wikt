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
#ifndef DEBUG_H_
#define DEBUG_H_

#include <QString>
#include <string>

#define ASSERTS_ENABLED

/// Adds a message to console output.
#define COUT(message) Debug::consoleOut(QString("%1").arg(message), __FILE__, __LINE__, __FUNCTION__)
/// Adds a message to console error output.
#define CERR(message) Debug::consoleErr(QString("%1").arg(message), __FILE__, __LINE__, __FUNCTION__)

#define CHECK(__expr) { \
  if (!(__expr)) { \
    Debug::consoleErr((#__expr), __FILE__, __LINE__, __FUNCTION__); \
    Debug::dialogErr((#__expr), __FILE__, __LINE__, __FUNCTION__); \
  } \
}

#define CHECK_MSG(__expr, __msg) { \
  if (!(__expr)) { \
    Debug::consoleErr(QString("%1 (expr: %2)").arg(__msg, #__expr), __FILE__, __LINE__, __FUNCTION__); \
    Debug::dialogErr(QString("%1 (expr: %2)").arg(__msg, #__expr),  __FILE__, __LINE__, __FUNCTION__); \
  } \
}

#define MSG(__msg) { \
  Debug::consoleErr(__msg, __FILE__, __LINE__, __FUNCTION__); \
  Debug::dialogErr(__msg,  __FILE__, __LINE__, __FUNCTION__); \
}

#ifdef ASSERTS_ENABLED
#define ASSERT(__expr) CHECK(__expr);
#else
#define ASSERT(__expr) {}
#endif

class Debug
{
public:
  /// Adds a message to console output.
  static void consoleOut(const QString &message, const char *file, int line, const char *func);
  /// Adds a message to console error output.
  static void consoleErr(const QString &message, const char *file, int line, const char *func);
  /// Displays a box with error message.
  /// Includes stack trace.
  static void dialogErr(const QString &message, const char *file, int line, const char *func);
};

#endif /* DEBUG_H_ */
