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
#include "mediautils.h"

MediaUtils::ImageType MediaUtils::imageTypeFromFileName(const QString &fileName)
{
  if (fileName.endsWith(".gif", Qt::CaseInsensitive)) return Gif;
  else if (fileName.endsWith(".jpg", Qt::CaseInsensitive)) return Jpg;
  else if (fileName.endsWith(".jpeg", Qt::CaseInsensitive)) return Jpg;
  else if (fileName.endsWith(".png", Qt::CaseInsensitive)) return Png;
  return Invalid;
}

const char *MediaUtils::toQtImageFormatId(ImageType imageType)
{
  switch (imageType)
  {
  case Gif: return "GIF";
  case Jpg: return "JPG";
  case Png: return "PNG";
  case Invalid:
  default:  return "";
  }
}


