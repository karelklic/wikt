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

// Conducting the whole scanning and parsing of Calc++.
class ExprDriver
{
public:
  ExprDriver();
  virtual ~ExprDriver();

  double result() const { return _result; }
  void setResult(double result) { _result = result; _resultChanged = true; }
  QString resultString() const
  {
    if (!_resultChanged)
      return "";
    return QString("%1").arg(_result);
  }


  // Handling the scanner.
  void scan_begin();
  void scan_end();

  // Handling the parser.
  void parse(const std::string& input);

  // Error handling.
  void error(const yy::location& l, const std::string& m);
  void error(const std::string& m);

protected:
  std::string _input;

  bool _traceScanning;
  bool _traceParsing;

  double _result;
  bool _resultChanged;
};

#endif /* EXPRDRIVER_H_ */
