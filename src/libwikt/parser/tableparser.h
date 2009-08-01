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
#ifndef TABLE_H_
#define TABLE_H_

#include "prerequisites.h"

class TableParser
{
  friend class TableRowParser;
  friend class TableCellParser;
  friend class TableHeadParser;
  friend class TableCaptionParser;
public:
  /// Returns 0 if the buffer contents cannot be
  /// parsed as a heading.
  static TableNode *parse(Buffer &buffer);

protected:
  static AttributeGroupNode *parseAttributes(QString text);

  static void parseAttributes(AttributeGroupNode *parent,
      QString &text, const QString &regex);
};

#endif /* TABLE_H_ */
