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
#ifndef LIBWIKT_DOM_ATTRIBUTE_NODE_H
#define LIBWIKT_DOM_ATTRIBUTE_NODE_H

#include "node.h"

class AttributeNode : public Node
{
public:
  AttributeNode(const QString &name, bool isNull);
  virtual QString toXHtml() const;
  virtual QString toXml(int indentLevel) const;

  const QString &name() const { return _name; }
  QString value() const { return toText(); }

protected:
  QString _name;
  bool _isNull;
};

#endif
