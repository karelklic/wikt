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
#include "ProfilerView.h"
#include "Profiler.h"
#include <QTableWidget>

//===========================================================================
ProfilerView::ProfilerView()
  : QDockWidget(tr("Profiler results"))
{
  setAllowedAreas(Qt::NoDockWidgetArea);
  setFeatures(QDockWidget::AllDockWidgetFeatures);

  _table = new QTableWidget(this);
  //  No editing possible.
  _table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  setWidget(_table);
}

//===========================================================================
void ProfilerView::show()
{
  _table->resizeColumnsToContents();
  QDockWidget::show();
}

//===========================================================================
void ProfilerView::ProfilerView::setRowCount(int count)
{
  _table->setRowCount(count);
}

//===========================================================================
void ProfilerView::setColumnCount(int count)
{
  _table->setColumnCount(count);
}

//===========================================================================
void ProfilerView::setItem(int row, int column, const QString &value)
{
  QTableWidgetItem *item = new QTableWidgetItem(value);
  _table->setItem(row, column, item);
}

//===========================================================================
void ProfilerView::setHorizontalHeaderItem(int column, const QString &value)
{
  QTableWidgetItem *item = new QTableWidgetItem(value);
  _table->setHorizontalHeaderItem(column, item);
}
