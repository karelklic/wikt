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
#ifndef WIKT_FIND_PANEL_H
#define WIKT_FIND_PANEL_H

#include <QDockWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QCheckBox;
QT_END_NAMESPACE

class FindPanel : public QDockWidget
{
  Q_OBJECT
public:
  /// Standard constructor.
  FindPanel(QWidget *parent = 0);

  virtual void setVisible(bool visible);

protected:
  virtual void keyPressEvent(QKeyEvent *event);

public slots:
  void previousClicked();
  void nextClicked();
  void textChanged(const QString &text);

private:
  /// A line where user write text for search.
  QLineEdit *_textEdit;

  QPushButton *_close;
  QPushButton *_previous;
  QPushButton *_next;
  QCheckBox *_caseSensitive;
};

#endif
