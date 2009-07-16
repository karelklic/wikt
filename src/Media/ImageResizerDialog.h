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
#ifndef IMAGERESIZERDIALOG_H
#define IMAGERESIZERDIALOG_H

#include <QtGui/QDialog>
#include "ui_ImageResizerDialog.h"

class ImageResizer;

class ImageResizerDialog : public QDialog
{
  Q_OBJECT
public:
  ImageResizerDialog(QWidget *parent = 0);
  ~ImageResizerDialog();

public slots:
  /// Activated when user clicks Browse button for source file.
  void onBrowseSourceFileButtonClick();
  /// Activated when user clicks Browse button for media directory.
  void onBrowseMediaDirectoryButtonClick();
  /// Activated when user clicks Start/Cancel button.
  void onStartButtonClick();
  /// Activated when the conversion is finished.
  void onWorkFinished();
  /// Activated when the content of logger window is changed.
  void onReportChanged();
  /// Stores the path to application settings.
  void onSourceFileEditChanged();
  /// Stores the path to application settings.
  void onMediaDirectoryEditChanged();

private:
  Ui::ImageResizerDialogClass ui;

  ImageResizer *_resizer;

  /// Mode of the start button.
  bool _startButtonStarts;
};

#endif // IMAGERESIZERDIALOG_H
