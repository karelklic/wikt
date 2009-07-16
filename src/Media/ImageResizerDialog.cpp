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
#include "ImageResizerDialog.h"
#include "ImageResizer.h"
#include <QFileDialog>
#include <QSettings>

//===========================================================================
ImageResizerDialog::ImageResizerDialog(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);

  // Set paths from application settings.
  QSettings settings;
  ui.sourceFileEdit->setText(
      settings.value("imageResizerDialogSourceFile", "").toString());
  ui.mediaDirectoryEdit->setText(
      settings.value("imageResizerDialogMediaDirectory", "").toString());

  // Connect signals and slots
  connect(ui.browseSourceFileButton, SIGNAL(clicked()),
      this, SLOT(onBrowseSourceFileButtonClick()));
  connect(ui.browseMediaDirectoryButton, SIGNAL(clicked()),
      this, SLOT(onBrowseMediaDirectoryButtonClick()));
  connect(ui.startButton, SIGNAL(clicked()),
      this, SLOT(onStartButtonClick()));
  connect(ui.reportEdit, SIGNAL(textChanged()),
      this, SLOT(onReportChanged()));
  connect(ui.sourceFileEdit, SIGNAL(textChanged(const QString&)),
      this, SLOT(onSourceFileEditChanged()));
  connect(ui.mediaDirectoryEdit, SIGNAL(textChanged(const QString&)),
      this, SLOT(onMediaDirectoryEditChanged()));
}

//===========================================================================
ImageResizerDialog::~ImageResizerDialog()
{
  if (_resizer)
    delete _resizer;
}

//===========================================================================
void ImageResizerDialog::onBrowseSourceFileButtonClick()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Select Format3 file",
      QDir::homePath(), "Format3 Files (*.ei3)");
  if (fileName.length() == 0) return;
  ui.sourceFileEdit->setText(fileName);

  if (ui.mediaDirectoryEdit->text().length() != 0) return;
  QFileInfo fi(fileName);
  QString mediaDir = fi.path() + "/" + "Media";
  ui.mediaDirectoryEdit->setText(mediaDir);
}

//===========================================================================
void ImageResizerDialog::onBrowseMediaDirectoryButtonClick()
{
  QString dir = QFileDialog::getExistingDirectory(this, "Media directory",
      QDir::homePath());
  if (dir.length() == 0) return;
  ui.mediaDirectoryEdit->setText(dir);
}

//===========================================================================
void ImageResizerDialog::onStartButtonClick()
{
  ui.sourceFileEdit->setEnabled(!_startButtonStarts);
  ui.browseSourceFileButton->setEnabled(!_startButtonStarts);
  ui.mediaDirectoryEdit->setEnabled(!_startButtonStarts);
  ui.browseMediaDirectoryButton->setEnabled(!_startButtonStarts);
  ui.startButton->setText(_startButtonStarts ? "Cancel" : "Start");
  if (_startButtonStarts)
  {
    ui.reportEdit->setStyleSheet("background-color:white");
    _resizer = new ImageResizer(ui.sourceFileEdit->text(), ui.mediaDirectoryEdit->text());
    connect(_resizer, SIGNAL(finished()), this, SLOT(onWorkFinished()));
    connect(_resizer, SIGNAL(log(const QString &)), ui.reportEdit, SLOT(appendPlainText(const QString&)));
    _resizer->start();
    _startButtonStarts = false;
  }
  else
    _resizer->requestTermination();

}

//===========================================================================
void ImageResizerDialog::onWorkFinished()
{
  // Start button to initial state.
  _startButtonStarts = true;
  ui.startButton->setText("Start");

  // Indicate success if the converter was not terminated.
  if (!_resizer->terminated())
  {
    ui.reportEdit->setStyleSheet("background-color:lightgreen");
    QApplication::beep();
  }

  // Delete the old conversion object.
  delete _resizer;
  _resizer = 0;

  // Enable GUI items.
  ui.sourceFileEdit->setEnabled(true);
  ui.browseSourceFileButton->setEnabled(true);
  ui.mediaDirectoryEdit->setEnabled(true);
  ui.browseMediaDirectoryButton->setEnabled(true);
  ui.startButton->setEnabled(true);
}

//===========================================================================
void ImageResizerDialog::onReportChanged()
{
  ui.reportEdit->ensureCursorVisible();
}

//===========================================================================
void ImageResizerDialog::onSourceFileEditChanged()
{
  QSettings settings;
  settings.setValue("imageResizerDialogSourceFile", ui.sourceFileEdit->text());
}

//===========================================================================
void ImageResizerDialog::onMediaDirectoryEditChanged()
{
  QSettings settings;
  settings.setValue("imageResizerDialogMediaDirectory", ui.mediaDirectoryEdit->text());
}
