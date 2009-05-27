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
#include "ExprDriver.h"
#include "ExprParser.tab.hpp"
#include "../../../../Prerequisites.h"
#include <sstream>

//===========================================================================
ExprDriver::ExprDriver(const QString &entryName) : _entryName(entryName),
  _traceScanning(false), _traceParsing(false),
  _result(0), _resultChanged(false), _errorOccurred(false)
{
}

//===========================================================================
ExprDriver::~ExprDriver()
{
}

//===========================================================================
QString ExprDriver::resultString() const
{
  if (_errorOccurred)
    return _lastError;
  if (!_resultChanged)
    return "";
  return QString("%1").arg(_result);
}

//===========================================================================
void ExprDriver::parse(const std::string &input)
{
  _input = input;
  scan_begin();
  yy::ExprParser parser(*this);
  parser.set_debug_level(_traceParsing);
  parser.parse();
  scan_end();
}

//===========================================================================
void ExprDriver::error(const yy::location& l, const std::string& m)
{
  std::stringstream ss;
  ss << l << ": " << m;
  error(ss.str());
}

//===========================================================================
void ExprDriver::error(const std::string& message)
{
  _lastError = QString("Error while parsing entry \"%1\", input \"%2\": %3")
      .arg(_entryName)
      .arg(QString::fromStdString(_input))
      .arg(QString::fromStdString(message));
  _errorOccurred = true;
  CERR(_lastError);
}
