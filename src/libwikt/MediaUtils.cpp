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
#include "MediaUtils.h"

//===========================================================================
const char *MediaUtils::toQtImageFormatId(const QString &fileName)
{
  // todo: move to QMap, will be probably faster
  if (fileName.endsWith(".bmp", Qt::CaseInsensitive)) return "BMP";
  else if (fileName.endsWith(".gif", Qt::CaseInsensitive)) return "GIF";
  else if (fileName.endsWith(".jpg", Qt::CaseInsensitive)) return "JPG";
  else if (fileName.endsWith(".jpeg", Qt::CaseInsensitive)) return "JPG";
  else if (fileName.endsWith(".png", Qt::CaseInsensitive)) return "PNG";
  else if (fileName.endsWith(".pbm", Qt::CaseInsensitive)) return "PBM";
  else if (fileName.endsWith(".pgm", Qt::CaseInsensitive)) return "PGM";
  else if (fileName.endsWith(".ppm", Qt::CaseInsensitive)) return "PPM";
  else if (fileName.endsWith(".tiff", Qt::CaseInsensitive)) return "TIFF";
  else if (fileName.endsWith(".xbm", Qt::CaseInsensitive)) return "XBM";
  else if (fileName.endsWith(".xpm", Qt::CaseInsensitive)) return "XPM";
  return "";
}


