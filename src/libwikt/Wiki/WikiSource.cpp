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
#include "../Media/MediaUtils.h"
#include <QSvgRenderer>
#include <QImage>

static WikiSource *instance = 0;

//===========================================================================
WikiSource::WikiSource(QObject *parent) : QObject(parent)
{
  ::instance = this;
  static const QString PATH_A("../data/");
  static const QString PATH_B("/usr/share/wikt/");

  QString dictionaryData;
  static const QString DICT_NAME("enwiktionary-20090203-pages-articles.ei4");
  if (QFile::exists(PATH_A + DICT_NAME))
    dictionaryData = PATH_A + DICT_NAME;
  else if (QFile::exists(PATH_B + DICT_NAME))
    dictionaryData = PATH_B + DICT_NAME;
  _reader = new Format4Reader(dictionaryData);

  QString mediaData;
  static const QString MEDIA_NAME("enwiktionary-20090203-pages-articles.eim");
  if (QFile::exists(PATH_A + MEDIA_NAME))
    mediaData = PATH_A + MEDIA_NAME;
  else if (QFile::exists(PATH_B + MEDIA_NAME))
    mediaData = PATH_B + MEDIA_NAME;
  _mediaReader = new MediaReader(mediaData);
}

//===========================================================================
WikiSource::~WikiSource()
{
  qDeleteAll(_cache.values());
  delete _reader;
  delete _mediaReader;
}

//===========================================================================
WikiSource &WikiSource::instance()
{
  return *::instance;
}

//===========================================================================
bool WikiSource::exist(const QString &entryName, bool useCache /*= true*/)
{
  if (useCache)
    return cached(entryName)->source() != "";
  else
    return _reader->exist(entryName);
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
  typedef QMap<QString, WikiSourceCacheItem*>::const_iterator It;
  for (It i = _cache.constBegin(); i != _cache.constEnd(); ++i)
    i.value()->invalidateSectionVisibility();
}

//===========================================================================
void WikiSource::translationSettingsChanged()
{
  typedef QMap<QString, WikiSourceCacheItem*>::const_iterator It;
  for (It i = _cache.constBegin(); i != _cache.constEnd(); ++i)
    i.value()->invalidateTranslationSettings();
}

//===========================================================================
QByteArray WikiSource::media(const QString &fileName)
{
  return _mediaReader->source(fileName);
}

//===========================================================================
QSize WikiSource::imageSize(const QString &fileName)
{
  // Load raw image from media archive.
  QByteArray source = media(fileName);

  // Determine initial image width and height.
  if (fileName.endsWith(".svg", Qt::CaseInsensitive))
  {
    QSvgRenderer svg(source);
    return svg.defaultSize();
  }
  else
  {
    QImage image = QImage::fromData(source, MediaUtils::toQtImageFormatId(fileName));
    return image.size();
  }
}

//===========================================================================
WikiSourceCacheItem *WikiSource::cached(const QString &entryName)
{
  if (_cache.contains(entryName))
    return _cache.value(entryName);

  QString source = _reader->source(entryName);

  // Implementation of REDIRECTs.
  if (source.trimmed().startsWith("#REDIRECT", Qt::CaseInsensitive))
  {
    int start = source.indexOf("[[");
    if (start == -1) return cached("Wikt:Redirect Error");
    int end = source.indexOf("]]", start);
    if (end == -1) return cached("Wikt:Redirect Error");
    QString redirName = source.mid(start + 2, end - start - 2);
    source = QString("<small>(Redirected from \"%1\")</small><br/>").arg(entryName);
    source += _reader->source(redirName);

    WikiSourceCacheItem *item = new WikiSourceCacheItem(redirName, source);
    _cache.insert(entryName, item);
    return item;
  }

  WikiSourceCacheItem *item = new WikiSourceCacheItem(entryName, source);
  _cache.insert(entryName, item);
  return item;
}
