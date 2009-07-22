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
#ifndef LANGUAGESTATISTIC_H_
#define LANGUAGESTATISTIC_H_

#include <QList>
class Node;

class LanguageStatistic
{
public:
  LanguageStatistic();

  /// @param nodes
  ///   Nodes that belong to certain language section.
  void visit(const QList<const Node*> &nodes);

  int entryCount() const { return _entryCount; }
  int definitionCount() const { return _glossCount + _formOfCount; }
  int glossCount() const { return _glossCount; }
  int formOfCount() const { return _formOfCount; }

private:
  /// Number of entries.
  int _entryCount;
  /// Number of full glossary definitions.
  int _glossCount;
  /// Number of form-of definitions.
  int _formOfCount;
};

#endif /* LANGUAGESTATISTIC_H_ */
