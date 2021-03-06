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
/* This file is required by commandPrepToMid. */
#ifndef FORMAT2_READER_H_
#define FORMAT2_READER_H_

#include <QString>
#include <QFile>
#include <QMap>

class Format2Reader
{
public:
  /// Standard constructor.
  Format2Reader(const QString &fileName);
  virtual ~Format2Reader();

  /// Cached. Implements redirects and entry name changes
  /// that makes this method suitable for obtaining
  /// template sources, but not for reading common entries.
  virtual QString sourceTemplate(QString entryName);

  virtual bool exist(QString entryName);

  /// @param offset
  ///   Offset between 0 and entry count.
  QString source(quint32 offset);
  /// @param offset
  ///  Offset between 0 and file size.
  QString sourceDirect(qint64 offset);

  /// Returns number of entries in the file.
  quint32 entryCount() const { return _entryCount; }

  typedef QMap<QString, qint64> EntryMap;
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


#endif /* FORMAT2_READER_H_ */
