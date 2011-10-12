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
/* This file is required by commandMidToDict. */
#ifndef FORMAT4WRITER_H_
#define FORMAT4WRITER_H_

#include <QString>
#include <QTemporaryFile>
#include <QPair>
#include <QList>

class Format4Writer
{
public:
  Format4Writer(const QString &targetFileName);

  void addEntry(const QString &name, const QString &contents);
  void addCategory(const QString &name, const QString &contents, const QStringList &subcategories, const QStringList &entries);
  void close();

private:
  QString _targetFileName;

  typedef QPair<QString, qint64> Link;
  QList<Link> _links;

  /// Temporary file with entries without indices.
  QTemporaryFile _temporaryFile;
};

#endif /* FORMAT4WRITER_H_ */
