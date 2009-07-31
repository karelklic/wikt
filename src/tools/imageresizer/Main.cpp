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
#include <libwikt/Format3Reader.h>
#include <libwikt/Tree/LinkNode.h>
#include <libwikt/Tree/LinkTargetNode.h>
#include <libwikt/Tree/ArticleNode.h>
#include <libwikt/Parser/ArticleParser.h>
#include <QCoreApplication>
#include <QTextStream>
#include <QDirIterator>
#include <QImage>
#include <QMap>

struct Image
{
  QString _filePath;
  QSize _originalSize;
  QList<QSize> _linkSizes;
  Image() {}
  Image(QString filePath, QSize originalSize) : _filePath(filePath), _originalSize(originalSize) {}
};

//===========================================================================
int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);

  if (argc != 3)
  {
    QTextStream err(stderr, QIODevice::WriteOnly);
    err << "Invalid number of arguments." << endl;
    err << QString("Usage: %1 [SOURCE] [MEDIA]").arg(argv[0]) << endl;
    err << "SOURCE - Format3 dictionary file with entries." << endl;
    err << "MEDIA - Directory with all media files." << endl;
    return -1;
  }

  QTextStream out(stdout, QIODevice::WriteOnly);
  out << "Getting sizes..." << endl;

  QMap<QString, Image> sizes; // key=filename
  QDirIterator dir(argv[2], QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
  while (dir.hasNext())
  {
    dir.next();

    // Some SVG files (Villainc.svg) cause crash of the QImage loader.
    // We do not need to resize them.
    if (dir.fileName().endsWith(".svg", Qt::CaseInsensitive))
      continue;

    QImage image(dir.filePath());
    if (image.isNull()) continue;
    out << QString(" image %1").arg(dir.fileName()) << endl;
    sizes.insert(dir.fileName(), Image(dir.filePath(), image.size()));
  }
  out << "Getting sizes done." << endl;

  out << "Checking entries..." << endl;
  Format3Reader reader(argv[1]);
  int counter = 0;
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
      LinkNode::Image image = link->getImageParams();
      sizes[fileName]._linkSizes.append(image.size);
    }
    delete node;

    // Page count.
    ++counter;
    if (counter % 1000 == 0)
      out << QString("Entries processed: %1").arg(counter) << endl;
  }
  out << "Checking entries done..." << endl;

  out << "Resizing..." << endl;
  for (QMap<QString, Image>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it)
  {
    // The following check fails.
    //CHECK(it.value()._linkSizes.count() > 0);

    QSize maxSize(0, 0);
    foreach(QSize size, it.value()._linkSizes)
    {
      if (size.width() < 0) // not valid
        size.setWidth(it.value()._originalSize.width() * size.height() / (double)it.value()._originalSize.height());
      if (size.height() < 0) // not valid
        size.setHeight(it.value()._originalSize.height() * size.width() / (double)it.value()._originalSize.width());

      int pixelCount = size.width() * size.height();
      if (pixelCount > maxSize.width() * maxSize.height())
        maxSize = size;
    }

    // Only resize the image if the resulting image is smaller.
    int originalPixelCount = it.value()._originalSize.width() * it.value()._originalSize.height();
    if (maxSize.width() * maxSize.height() < originalPixelCount)
    {
      // Debug
      //COUT(it.value()._filePath);

      QImage image(it.value()._filePath);
      QImage newImage = image.scaledToWidth(maxSize.width(), Qt::SmoothTransformation);
      newImage.save(it.value()._filePath);
      out << QString("Resized %1 from %2x%3 to %4x%5")
          .arg(it.key())
          .arg(it.value()._originalSize.width())
          .arg(it.value()._originalSize.height())
          .arg(maxSize.width())
	.arg(maxSize.height()) << endl;
    }
  }
  out << "Resizing done..." << endl;

  return 0;
}
