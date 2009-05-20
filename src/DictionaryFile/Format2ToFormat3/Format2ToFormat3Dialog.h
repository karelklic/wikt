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
#ifndef EICTOEIFGENERATORDIALOG_H
#define EICTOEIFGENERATORDIALOG_H

#include "../../Prerequisites.h"
#include <QDialog>
#include "ui_Format2ToFormat3Dialog.h"

class Format2ToFormat3Converter;

class Format2ToFormat3Dialog : public QDialog
{
  Q_OBJECT
public:
  /// Standard constructor.
  Format2ToFormat3Dialog(QWidget *parent = 0);
  ~Format2ToFormat3Dialog();

public slots:
  /// Activated when user clicks Browse button for source file.
  void onBrowseSourceButtonClick();
  /// Activated when user clicks Browse button for destination file.
  void onBrowseDestinationButtonClick();
  /// Activated when user clicks Start/Cancel button.
  void onStartButtonClick();
  /// Activated when the conversion is finished.
  void onWorkFinished();
  /// Activated when the content of logger window is changed.
  void onReportChanged();
  /// Activated when the source file path is changed.
  /// Stores the path to application settings.
  void onSourceEditChanged();
  /// Activated when the destination file path is changed.
  /// Stores the path to application settings.
  void onDestinationEditChanged();

private:
  Ui::Format2ToFormat3DialogClass ui;
  Format2ToFormat3Converter *_converter;

  /// Mode of the start button.
  bool _startButtonStarts;
};

#endif // EICTOEIFGENERATORDIALOG_H
