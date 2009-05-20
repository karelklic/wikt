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
#ifndef EICREADER_H_
#define EICREADER_H_

#include "../../Prerequisites.h"
#include <QString>
#include <QFile>
#include <QMap>

class Format2Reader
{
public:
  /// Standard constructor.
  Format2Reader(const QString &fileName);
  virtual ~Format2Reader();

  // Cached.
  virtual QString source(QString entryName);
  virtual bool exist(QString entryName);
  /// @param offset
  ///   Offset between 0 and entry count.
  QString source(int offset);
  /// @param offset
  ///  Offset between 0 and file size.
  QString sourceDirect(int offset);

  /// Returns number of entries in the file.
  int entryCount() const { return _entryCount; }

  typedef QMap<QString, size_t> EntryMap;
  const EntryMap &entries() const { return _links; }

protected:
  /// Constructor for testing purposes only.
  Format2Reader();

  QFile _file;
  quint32 _entryCount;
  EntryMap _links;

  typedef QMap<QString, QString> CacheMap;
  CacheMap _templateCache;
};


#endif /* EICREADER_H_ */
