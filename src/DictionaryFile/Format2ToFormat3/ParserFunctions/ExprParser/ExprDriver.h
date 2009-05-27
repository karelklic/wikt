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
#ifndef EXPRDRIVER_H_
#define EXPRDRIVER_H_

#include "location.hh"
#include <QString>

/// Conducting the whole scanning and parsing of #expr.
/// http://meta.wikimedia.org/wiki/Help:Calculation
class ExprDriver
{
public:
  ExprDriver(const QString &entryName);
  virtual ~ExprDriver();

  double result() const { return _result; }
  void setResult(double result) { _result = result; _resultChanged = true; }
  QString resultString() const;

  // Handling the scanner.
  void scan_begin();
  void scan_end();

  // Handling the parser.
  void parse(const std::string& input);

  // Error handling.
  void error(const yy::location& l, const std::string& m);
  void error(const std::string& message);

protected:
  QString _entryName;
  std::string _input;

  bool _traceScanning;
  bool _traceParsing;

  double _result;
  bool _resultChanged;

  bool _errorOccurred;
  QString _lastError;
};

#endif /* EXPRDRIVER_H_ */
