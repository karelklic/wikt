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
#ifndef FORMAT3TOFORMAT4DIALOG_H
#define FORMAT3TOFORMAT4DIALOG_H

#include "../../Prerequisites.h"
#include <QDialog>
#include "ui_Format3ToFormat4Dialog.h"

class Format3ToFormat4Converter;

class Format3ToFormat4Dialog : public QDialog
{
  Q_OBJECT
public:
  /// Standard constructor.
  Format3ToFormat4Dialog(QWidget *parent = 0);
  ~Format3ToFormat4Dialog();

public slots:
  /// Activated when user clicks Browse button for source file.
  void onBrowseSourceButtonClick();
  /// Activated when user clicks Browse button for source media file.
  void onBrowseSourceMediaButtonClick();
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
  /// Activated when the source media file path is changed.
  /// Stores the path to application settings.
  void onSourceMediaEditChanged();
  /// Activated when the destination file path is changed.
  /// Stores the path to application settings.
  void onDestinationEditChanged();

private:
  Ui::Format3ToFormat4DialogClass ui;
  Format3ToFormat4Converter *_converter;

  /// Mode of the start button.
  bool _startButtonStarts;
};

#endif // FORMAT3TOFORMAT4DIALOG_H
