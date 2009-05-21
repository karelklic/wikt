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
#ifndef WIKI_WIKI_SOURCE_H
#define WIKI_WIKI_SOURCE_H

#include <QString>
#include <QMap>
#include <QObject>
class Format4Reader;
class MediaReader;
class ArticleNode;
class WikiSourceCacheItem;

/// Caches the entry source text, parsed tree, XHTML representation.
class WikiSource : public QObject
{
  Q_OBJECT
public:
  WikiSource(QObject *parent);
  ~WikiSource();
  bool exist(const QString &entryName);
  const QString &source(const QString &entryName);
  /// Do not delete it.
  ArticleNode *tree(const QString &entryName);
  const QString &xhtml(const QString &entryName);

  void sectionVisibilityChanged();
  void translationSettingsChanged();

  QByteArray media(const QString &fileName);

private:
  WikiSourceCacheItem *cached(const QString &entryName);

  QMap<QString, WikiSourceCacheItem*> _cache;
  Format4Reader *_reader;
  MediaReader *_mediaReader;
};

#endif /* WIKI_WIKI_SOURCE_H */
