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
#ifndef EXTERNALLINKNODE_H_
#define EXTERNALLINKNODE_H_

#include "Node.h"
#include <QString>

/// Represents a wiki link such as "[http://url/ link]".
class ExternalLinkNode : public Node
{
public:
  /// Standard constructor.
  ExternalLinkNode(const QString &url, const QString &text);

  virtual QString toXHtml() const;
  virtual QString toXml(int indentLevel) const;

protected:
  QString _url;
  QString _text;
};

#endif /* EXTERNALLINKNODE_H_ */
