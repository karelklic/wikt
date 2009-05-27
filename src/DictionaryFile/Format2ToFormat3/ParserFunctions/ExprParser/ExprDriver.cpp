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
ExprDriver::ExprDriver() : _traceScanning(false),
  _traceParsing(false), _result(0), _resultChanged(false)
{
}

//===========================================================================
ExprDriver::~ExprDriver()
{
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
  ss << l << ": " << m << " (\"" << _input << "\")";
  CERR(QString("Error while parsing input %1: %2")
      .arg(QString::fromStdString(_input))
      .arg(QString::fromStdString(ss.str())));
}

//===========================================================================
void ExprDriver::error(const std::string& m)
{
  CERR(QString("Error while parsing input %1: %2")
      .arg(QString::fromStdString(_input))
      .arg(QString::fromStdString(m)));
}
