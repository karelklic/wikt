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
#ifndef LIBWIKT_HTML_ELEMENT_NODE_H_
#define LIBWIKT_HTML_ELEMENT_NODE_H_

#include "node.h"
class TableNode;

class HtmlElementNode : public Node
{
public:
  /// @param paired
  ///   <tag></tag> is paired
  ///   <tag /> is not paired.
  HtmlElementNode(const QString &name, const QString &params, bool paired);
  virtual QString toXHtml() const;
  virtual QString toXml(int indentLevel = 0) const;

  bool paired() const { return _paired; }
  const QString &name() const { return _name; }
  const QString &params() const { return _params; }

  /// Checks if this node is a See Also <div> node, which
  /// is used at the top of the page to show variants of
  /// the entry name.
  bool isSeeAlsoNode() const;

  TableNode *findTranslationTable() const;

protected:
  QString _name;
  QString _params;
  bool _paired;
};

#endif /* LIBWIKT_HTML_ELEMENT_NODE_H_ */
