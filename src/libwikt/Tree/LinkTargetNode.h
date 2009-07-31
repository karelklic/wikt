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
#ifndef LIBWIKT_DOM_LINK_TARGET_NODE_H
#define LIBWIKT_DOM_LINK_TARGET_NODE_H

#include "Node.h"
#include "../Namespace.h"
#include "../Language.h"
#include "../Project.h"

/// Format of Link target: project:language:namespace:entry#heading
/// Project can be nothing (meaning Wiktionary), "w:", "wikipedia:", "m:", "meta:", or some other.
/// Language can be nothing (meaning English), "cs:", "zh-min-nan:", "de:", or some other.
/// Namespace can be nothing (meaning Main), "Talk:", "Image:", "Category:", or some other.
/// Heading can be nothing, "#Czech", "#English", or some other.
/// TODO: check if it handles [[#Czech]] and it jumps to Czech section.
class LinkTargetNode : public Node
{
public:
  /// Standard constructor.
  /// @param text
  ///   Target link text."It has the format project:language:namespace:entry#heading,
  ///   where no part is mandatory. It must contain either entry or heading.
  LinkTargetNode(const QString &text);
  /// Returns the link as URL path, either internal or external.
  QString toXHtmlLink() const;
  /// Returns the)
  virtual QString toXml(int indentLevel = 0) const;
  virtual QString toText() const { return _text; }
  virtual QString toXHtml() const { return _text; }

  Namespace::Type namespace_() const { return _namespace; }
  Language::Type language() const { return _language; }
  /// Target project. It can be either Wiktionary or some
  /// other project, eg. Wikipedia.
  Project::Type project() const { return _project; }

  /// The page name only, without namespace etc.
  const QString &entry() const { return _entry; }
  /// The target heading without the # character.
  const QString &heading() const { return _heading; }

protected:
  Namespace::Type _namespace;
  Language::Type _language;
  Project::Type _project;

  /// Whole text as provided.
  QString _text;

  /// The page name only.
  QString _entry;
  /// The target heading without the # character.
  QString _heading;
};

#endif
