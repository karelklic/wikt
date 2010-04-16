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
#include "wikisourcecacheitem.h"
#include <libwikt/parser/articleparser.h>

//===========================================================================
static void
nodeToXHtml(const ArticleNode &node, QString &xhtmlResult)
{
  xhtmlResult = QString("<html><head>"
    "<link rel=\"stylesheet\" type=\"text/css\" href=\"special://stylesheet\" />"
    "  <script type=\"text/javascript\" src=\"special://javascript\"></script>"
    "</head><body>%1</body></html>").arg(node.toXHtml());
}

//===========================================================================
WikiSourceCacheItem::WikiSourceCacheItem(const QString &name, const QString &source)
  : _source(source), _invalidSectionVisibility(false), _invalidTranslationSettings(false)
{
  if (_source != "")
    {
      _node = ArticleParser::parse(name, source);
      _node->updateSectionVisibility();
      _node->updateTranslationSettings();
      nodeToXHtml(*_node, _xhtml);
    }
  else
    _node = 0;
}

//===========================================================================
WikiSourceCacheItem::~WikiSourceCacheItem()
{
  if (_node)
    delete _node;
}

//===========================================================================
ArticleNode *WikiSourceCacheItem::node()
{
  handleInvalidationFlags();
  return _node;
}

//===========================================================================
const QString &WikiSourceCacheItem::xhtml()
{
  handleInvalidationFlags();
  return _xhtml;
}

//===========================================================================
void WikiSourceCacheItem::handleInvalidationFlags()
{
  if (!_invalidSectionVisibility && !_invalidTranslationSettings)
    return;

  if (_invalidSectionVisibility)
    _node->updateSectionVisibility();
  if (_invalidTranslationSettings)
    _node->updateTranslationSettings();

  nodeToXHtml(*_node, _xhtml);
  _invalidSectionVisibility = false;
  _invalidTranslationSettings = false;
}
