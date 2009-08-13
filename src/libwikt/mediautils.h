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
#ifndef MEDIAUTILS_H_
#define MEDIAUTILS_H_

#include <QString>

class MediaUtils
{
public:
  /// Image types supported by Wikt. Qt supports more formats, but Wiktionary
  /// contains mostly pngs and jpegs.
  enum ImageType { Invalid, Gif, Jpg, Png };

  /// Detects image type from file name suffix.
  /// If the image type is not detected, image type Invalid is returned.
  /// @param fileName
  ///   File name with or without path. Only the end of the string is tested. 
  /// @returns
  ///   Image type or Invalid if the type is not detected.
  static ImageType imageTypeFromFileName(const QString &fileName);

  /// Converts image type to image format ID understandable by Qt.
  /// @param imageType
  ///   Must be valid image type and not Unknown.
  /// @returns
  ///   Qt identifier. Returned string/memory is owned by this function, do not delete it.
  ///   If imageType is invalid, pointer to empty string "" is returned.
  static const char *toQtImageFormatId(ImageType imageType);
};

#endif /* MEDIAUTILS_H_ */
