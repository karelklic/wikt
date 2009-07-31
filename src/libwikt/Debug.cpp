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
#include "Debug.h"
#include "Unicode.h"
//#include "ErrorDialog/ErrorDialog.h" TO BE ALTERNATED
#include <iostream>
#include <execinfo.h> // GCC-only stack trace
#include <cxxabi.h> //demangler for C++ names
#include <cstdlib>
#include <QMap>

//===========================================================================
void Debug::consoleOut(const QString &message, const char *file, int line, const char *func)
{
  std::cout << file << ":" << line << " (" << func << ")#"
    << Unicode::escape(message) << std::endl;
}

//===========================================================================
void Debug::consoleErr(const QString &message, const char *file, int line, const char *func)
{
  std::cerr << file << ":" << line << " (" << func << ")#"
    << Unicode::escape(message) << std::endl;
}

//===========================================================================
struct Error
{
  QString _file;
  int _line;
  QString _message;

  Error(const QString &file, int line, const QString &message)
    : _file(file), _line(line), _message(message)
  {}

  bool operator<(const Error &k) const
  {
    if (_file < k._file) return true;
    if (_file > k._file) return false;
    if (_line < k._line) return true;
    if (_line > k._line) return false;
    if (_message < k._message) return true;
    if (_message > k._message) return false;
    return false;
  }
};

//===========================================================================
void Debug::dialogErr(const QString &message, const char *file, int line, const char *func)
{
  static QMap<Error, bool> items;
  Error error(file, line, message);
  QMap<Error, bool>::iterator errorIt = items.find(error);
  if (errorIt == items.end())
    errorIt = items.insert(error, true);
  if (!errorIt.value()) return;

  // Get stack trace.
  // http://tombarta.wordpress.com/2008/08/01/c-stack-traces-with-gcc/
  // In order to make it working, the parameter "-rdynamic" must be passed to
  // the linker while linking the binary. In qmake that means
  // QMAKE_LFLAGS += -rdynamic.
  QList<QString> stackTrace;
  const size_t maxDepth = 100;
  void *stackAddrs[maxDepth];
  size_t stackDepth = backtrace(stackAddrs, maxDepth);
  char **stackStrings = backtrace_symbols(stackAddrs, stackDepth);
  for (size_t i = 0; i < stackDepth; ++i)
  {
    QString line = QString::fromAscii(stackStrings[i]);
    int start = line.indexOf("(");
    int end = line.indexOf("+", start);
    if (start != -1 && end != -1)
    {
      QString forDemangler = line.mid(start + 1, end - start - 1);
      int status;
      char *ret = abi::__cxa_demangle(forDemangler.toAscii().constData(),
          NULL, NULL, &status);
      if (ret)
      {
        stackTrace.append(QString::fromAscii(ret));
        free(ret);
        continue;
      }
    }
    stackTrace.append(line);
  }
  free(stackStrings);

  QString trace;
  foreach(QString s, stackTrace)
    trace += s + "\n";

  QString report;
  report = QString("Message: %1\nFile: %2\nFunction: %3\nLine: %4\nStack trace:\n%5")
    .arg(message).arg(file).arg(func).arg(line).arg(trace);

/* TEMPORARILY COMMENTED OUT
  ErrorDialog dialog(message, file, func, line, trace);
  int result = dialog.exec();
  if (result == ErrorDialog::Ignored)
    errorIt.value() = false;
*/
}
