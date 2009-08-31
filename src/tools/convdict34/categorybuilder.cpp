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
#include "categorybuilder.h"
#include <libwikt/namespace.h>
#include <QMap>
#include <QString>

class CategoryEntry
{
public:
  /// Contents in wiki markup.
  QString contents;

  /// Adds entry to this category. Entries which belongs to this category
  /// must be added this way. Both categories and entries from the main
  /// namespace are added this way.
  /// @param entry
  ///  Entry name.
  void addEntry(const QString &entry);

  /// Subcategories of this category.
  QList<QString> categories;
  /// Entries from the main namespace that belongs to this category.
  QList<QString> mainEntries;
};

//===========================================================================
void CategoryEntry::addEntry(const QString &entry)
{
  Namespace::Type ns = Namespace::instance().fromEntry(entry);
  if (ns == Namespace::Category)
    categories.append(entry);
  else
    mainEntries.append(entry);
}

static QMap<QString, CategoryEntry> categories;

//===========================================================================
void CatBuilder_addContents(const QString &categoryName, const QString &contents)
{
  QMap<QString, CategoryEntry>::iterator it = categories.find(categoryName);
  if (it == categories.end())
    it = categories.insert(categoryName, CategoryEntry());
  it.value().contents = contents;
}

//===========================================================================
/// Adds entry to certain category. Entries which belongs to some category
/// must be added this way. Both entries from the main namespace and 
/// subcategories are added this way.
/// @param entry
///  Entry name.
static void addLink(const QString &categoryName, const QString &entry)
{
  QMap<QString, CategoryEntry>::iterator it = categories.find(categoryName);
  if (it == categories.end())
    it = categories.insert(categoryName, CategoryEntry());
  it.value().addEntry(entry);
}

//===========================================================================
void CatBuilder_process(const QString &name, const ArticleNode &node)
{
  QStringList categories;
  node.getCategories(categories);
  foreach (const QString &category, categories)
    addLink("Category:" + category, name);
}

//===========================================================================
void CatBuilder_writeAll(Format4Writer &destination)
{
  static QMap<QString, CategoryEntry> categories;
  for (QMap<QString, CategoryEntry>::const_iterator it = categories.begin(); it != categories.end(); ++it)
    destination.addCategory(it.key(), it.value().contents, it.value().categories, it.value().mainEntries);
}
