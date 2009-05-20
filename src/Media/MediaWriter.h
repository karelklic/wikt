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
#ifndef MEDIAWRITER_H_
#define MEDIAWRITER_H_

#include "../Prerequisites.h"
#include <QString>
#include <QTemporaryFile>
#include <vector>

class MediaWriter
{
public:
  MediaWriter(const QString &targetFileName);

  void addEntry(const QString &name, const QByteArray &contents);
  void close();

private:
  QString _targetFileName;

  typedef std::pair<QString, size_t> Link;
  typedef std::vector<Link> LinkList;
  LinkList _links;

  /// Temporary file with entries without indices.
  QTemporaryFile _temporaryFile;
};

#endif /* MEDIAWRITER_H_ */
