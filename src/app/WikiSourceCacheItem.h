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
#ifndef WIKISOURCECACHEITEM_H_
#define WIKISOURCECACHEITEM_H_

#include <QString>

class ArticleNode;

class WikiSourceCacheItem
{
public:
  WikiSourceCacheItem(const QString &name, const QString &source);
  ~WikiSourceCacheItem();

  void invalidateSectionVisibility() { _invalidSectionVisibility = true; }
  void invalidateTranslationSettings() { _invalidTranslationSettings = true; }

  const QString &source() const { return _source; }
  ArticleNode *node();
  const QString &xhtml();

private:
  void handleInvalidationFlags();

  QString _source;
  ArticleNode *_node;
  QString _xhtml;
  bool _invalidSectionVisibility;
  bool _invalidTranslationSettings;
};

#endif /* WIKISOURCECACHEITEM_H_ */
