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
#ifndef PARAMETERLIST_H_
#define PARAMETERLIST_H_

#include <QMap>
#include <QString>

class ParameterList
{
public:
  ParameterList();

  void insert(QString key, QString value);
  void insert(QString value);

  bool contains(QString key) const { return _parameters.contains(key); }
  QString operator[](QString key) const;
  int size() const { return _parameters.size(); }

protected:
  int _positionalParameterCount;
  QMap<QString, QString> _parameters;
};

#endif /* PARAMETERLIST_H_ */
