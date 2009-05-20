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
#ifndef MEDIAPACKERDIALOG_H
#define MEDIAPACKERDIALOG_H

#include <QDialog>
#include "ui_MediaPackerDialog.h"

class MediaPacker;

class MediaPackerDialog : public QDialog
{
  Q_OBJECT
public:
  MediaPackerDialog(QWidget *parent = 0);
  ~MediaPackerDialog();

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
  Ui::MediaPackerDialogClass ui;

  MediaPacker *_packer;

  /// Mode of the start button.
  bool _startButtonStarts;
};

#endif // MEDIAPACKERDIALOG_H
