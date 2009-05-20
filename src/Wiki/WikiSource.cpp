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
#include "WikiSource.h"
#include "WikiSourceCacheItem.h"
#include "Tree/Article/ArticleNode.h"
#include "../DictionaryFile/Format4Reader.h"
#include "../Media/MediaReader.h"

//===========================================================================
WikiSource::WikiSource(QObject *parent) : QObject(parent)
{
  _reader = new Format4Reader("data/enwiktionary-20090203-pages-articles.ei4");
  _mediaReader = new MediaReader("data/enwiktionary-20090203-pages-articles.eim");
}

//===========================================================================
WikiSource::~WikiSource()
{
  qDeleteAll(_cache.values());
  delete _reader;
  delete _mediaReader;
}

//===========================================================================
bool WikiSource::exist(const QString &entryName)
{
  return cached(entryName)->source() != "";
}

//===========================================================================
const QString &WikiSource::source(const QString &entryName)
{
  return cached(entryName)->source();
}

//===========================================================================
ArticleNode *WikiSource::tree(const QString &entryName)
{
  return cached(entryName)->node();
}

//===========================================================================
const QString &WikiSource::xhtml(const QString &entryName)
{
  return cached(entryName)->xhtml();
}

//===========================================================================
void WikiSource::sectionVisibilityChanged()
{
  for (QMap<QString, WikiSourceCacheItem*>::const_iterator i = _cache.constBegin();
    i != _cache.constEnd();
    ++i)
  {
    i.value()->invalidateSectionVisibility();
  }
}

//===========================================================================
QByteArray WikiSource::media(const QString &fileName)
{
  return _mediaReader->source(fileName);
}

//===========================================================================
WikiSourceCacheItem *WikiSource::cached(const QString &entryName)
{
  if (_cache.contains(entryName))
    return _cache.value(entryName);

  WikiSourceCacheItem *item = new WikiSourceCacheItem(
      entryName, _reader->source(entryName));
  _cache.insert(entryName, item);
  return item;
}
