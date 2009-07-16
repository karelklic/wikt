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
#include "ImageResizer.h"
#include "MediaUtils.h"
#include "../DictionaryFile/Format3ToFormat4/Format3Reader.h"
#include "../Wiki/Tree/Link/LinkNode.h"
#include "../Wiki/Tree/Link/LinkTargetNode.h"
#include "../Wiki/Tree/Article/ArticleNode.h"
#include "../Wiki/Parser/ArticleParser.h"
#include <QDirIterator>
#include <QImage>
#include <QMap>

//===========================================================================
ImageResizer::ImageResizer(const QString& sourceFile,
    const QString& mediaDirectory)
    : _sourceFile(sourceFile), _mediaDirectory(mediaDirectory),
    _terminate(false)
{
}

//===========================================================================
void ImageResizer::run()
{
  log("Processing started.");

  log("Getting sizes...");
  QMap<QString, Image> sizes; // key=filename
  QDirIterator dir(_mediaDirectory, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
  while (dir.hasNext())
  {
    dir.next();
    QImage image(dir.filePath());
    if (image.isNull()) continue;
    log(QString(" image %1").arg(dir.fileName()));
    sizes.insert(dir.fileName(), Image(dir.filePath(), image.size()));

    // Termination.
    if (_terminate)
    {
      log("Processing terminated.");
      return;
    }
  }
  log("Getting sizes done.");

  log("Checking entries...");
  Format3Reader reader(_sourceFile);
  const Format3Reader::EntryMap &entries = reader.entries();
  for (Format3Reader::EntryMap::const_iterator it = entries.constBegin(); it != entries.constEnd(); ++it)
  {
    QString contents = reader.sourceDirect(it.value());
    ArticleNode *node = ArticleParser::parse(it.key(), contents);
    CHECK(node);
    QList<const LinkNode*> allLinks;
    node->findChildren(allLinks);
    foreach(const LinkNode *link, allLinks)
    {
      if (!link->isDisplayableImage()) continue;
      QString fileName = link->target().entry();
      if (!sizes.contains(fileName)) continue;
      LinkNode::Image image = link->getImageParams(sizes[fileName]._originalSize);
      sizes[fileName]._linkSizes.append(image.size);
    }
    delete node;

    // Termination.
    if (_terminate)
    {
      log("Processing terminated.");
      return;
    }
  }
  log("Checking entries done...");

  log("Resizing...");
  for (QMap<QString, Image>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it)
  {
    CHECK(it.value()._linkSizes.count() > 0);
    QSize maxSize(0, 0);
    foreach(const QSize &size, it.value()._linkSizes)
    {
      int pixelCount = size.width() * size.height();
      if (pixelCount > maxSize.width() * maxSize.height())
        maxSize = size;
    }

    // Only resize the image if the resulting image is smaller.
    int originalPixelCount = it.value()._originalSize.width() * it.value()._originalSize.height();
    if (maxSize.width() * maxSize.height() < originalPixelCount)
    {
      QImage image(it.value()._filePath);
      QImage newImage = image.scaledToWidth(maxSize.width(), Qt::SmoothTransformation);
      newImage.save(it.value()._filePath);
      log(QString("Resized %1 from %2x%3 to %4x%5")
          .arg(it.key())
          .arg(it.value()._originalSize.width())
          .arg(it.value()._originalSize.height())
          .arg(maxSize.width())
          .arg(maxSize.height()));
    }
  }
  log("Resizing done...");
}
