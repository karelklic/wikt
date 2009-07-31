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
#ifndef LIBWIKT_DOM_LINK_NODE_H
#define LIBWIKT_DOM_LINK_NODE_H

#include "../Node.h"
#include "../../Namespace.h"
#include "../../Language/Language.h"
#include "../../Project.h"
#include <QList>
#include <QSize>

class LinkTargetNode;
class LinkOptionsNode;

/// Represents a wiki [[link]] with optional options [[link|option1|option2]].
class LinkNode : public Node
{
public:
  /// Standard constructor.
  /// @param forcedLink
  ///   Forced links begin with a colon ("[[:link]]").
  ///   It indicates the link has no other function than to be a link.
  ///   So if it links a category, the entry is not added to the category and
  ///   the link is not hidden in the XHTML output as usual, but it is displayed,
  ///   linking to the category.
  /// @param emptyPipeAtEnd
  ///   http://meta.wikimedia.org/wiki/Help:Piped_link
  LinkNode(bool emptyPipeAtEnd, bool forcedLink);

  /// Returns the contents of this node as a XHTML code. If this node links
  /// to an image, the <img> tag is returned.
  virtual QString toXHtml() const;

  /// Returns the contents of this node as a XML element. Useful for debug
  /// purposes.
  virtual QString toXml(int indentLevel) const;

  /// Used by LinkConverter class.
  QString toWiki() const;

  /// Returns an external link representation of this link node.
  /// For example returns "[http://en.wiktionary.org/wiki/maso maso]"
  /// for node created from "[[maso]]".
  QString toExternalLinkWiki() const;

  /// Adds a child node.
  virtual void append(Node *child);

  /// Forced link is the one that begins with colon,
  /// such as [[:Category:Czech nouns]].
  bool forcedLink() const { return _forcedLink; }

  /// The link is in format [[link|]].
  bool emptyPipeAtEnd() const { return _emptyPipeAtEnd; }

  /// Returns the title of link. This is supposed to be read by users.
  QString xhtmlTitle() const;

  /// The link's target node. [[this is target|this is option1|this is option2]]
  LinkTargetNode &target() const { return *_target; }

  bool isInterwiki() const;

  int getOptionCount() const { return _options.size(); }
  LinkOptionsNode *getOption(int pos) const { return _options[pos]; }

  struct Image
  {
    enum ImageType
    {
      Simple, Thumbnail, Frame, Border
    } type;

    enum ImageLocation
    {
      Right, Left, Center, None, Default
    } location;

    /// Image maximal size to be displayed in pixels (max-width, max-height in CSS).
    QSize size;

    QString caption;

    /// size.isValid() is automatically false.
    Image() : type(Simple), location(Default) {}
  };

  bool isDisplayableImage() const;
  Image getImageParams() const;

protected:
  QString toXHtmlImage() const;

  /// http://meta.wikimedia.org/wiki/Help:Piped_link
  bool _emptyPipeAtEnd;
  /// A link starts with "[[:", so all its side effects are suppressed.
  /// For example if the link points to a category, the category is
  /// only linked, but the entry is not categorized.
  bool _forcedLink;

  LinkTargetNode *_target;
  QList<LinkOptionsNode*> _options;
};

#endif
