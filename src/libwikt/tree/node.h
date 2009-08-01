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
#ifndef LIBWIKT_DOM_NODE_H
#define LIBWIKT_DOM_NODE_H

#include "../prerequisites.h"
#include <QList>
#include <QString>

class AttributeGroupNode;

class Node
{
public:
  enum Type {
    None, Article, Paragraph, Heading, TextBlock, TextToken, ExtensionToken,
    PreBlock, PreLine, Bold, Italics, Link,
    LinkTarget, LinkOption, ExternalLink, Table, TableRow, TableCell,
    TableHead, TableCaption, Attribute, AttributeGroup,
    DefinitionList, DefinitionListTermItem, DefinitionListDefItem,
    BulletList, NumberedList, ListItem, HtmlElement, HtmlEntity
  };

  Node(Type type);
  virtual ~Node();

  /// The only way how to insert child nodes.
  /// Overload it to filter, monitor, or control node inserting.
  virtual void append(Node *child) { ASSERT(child); _children.append(child); }
  int count() const { return _children.count(); }
  Node *child(int i) const { return _children.at(i); }
  QList<Node*> &children() { return _children; }
  const QList<Node*> &children() const { return _children; }
  Node *last() const { return _children.last(); }
  Type type() const { return _type; }

  /// Finds all child nodes of specific node type.
  template<typename T>
  void findChildren(QList<T*> &destination, bool recursive = true) const
  {
    foreach(Node *child, _children)
    {
      if (recursive) child->findChildren(destination);
      T *node = dynamic_cast<T*>(child);
      if (node) destination.append(node);
    }
  }

  virtual QString toXHtml() const;
  virtual QString toXml(int indentLevel = 0) const;
  virtual QString toText() const;

  void setXHtmlVisibility(bool value) { _xhtmlVisible = value; }

  bool hasAttributeGroupChild() const;
  const AttributeGroupNode *getAttributeGroupChild() const;

protected:
  QString childrenToXHtml(bool skipAttributeGroup = true) const;
  QString childrenToXml(int indentLevel) const;
  QString childrenToText() const;
  static QString toXmlEscaped(const QString &text);

  // Whether the node is visible in the XHTML output.
  bool _xhtmlVisible;

private:
  QList<Node*> _children;
  Type _type;
};

#endif
