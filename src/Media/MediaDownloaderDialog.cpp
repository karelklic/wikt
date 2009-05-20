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
#include "MediaDownloaderDialog.h"
#include "MediaDownloader.h"
#include <QFileDialog>
#include <QTest>
#include <QSettings>

//===========================================================================
MediaDownloaderDialog::MediaDownloaderDialog(QWidget *parent)
  : QDialog(parent), _downloader(0), _startButtonStarts(true)
{
	ui.setupUi(this);

  // Set paths from application settings.
  QSettings settings;
  ui.sourceEdit->setText(
      settings.value("mediaDownloaderDialogSource", "").toString());
  ui.destinationEdit->setText(
      settings.value("mediaDownloaderDialogDestination", "").toString());
}

//===========================================================================
MediaDownloaderDialog::~MediaDownloaderDialog()
{
  if (_downloader)
    delete _downloader;
}

//===========================================================================
void MediaDownloaderDialog::onBrowseSourceButtonClick()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Select Format3 file",
      QDir::homePath(), "Format3 Files (*.ei3)");
  if (fileName.length() == 0) return;
  ui.sourceEdit->setText(fileName);

  if (ui.destinationEdit->text().length() != 0) return;
  QFileInfo fi(fileName);
  QString destinationDir = fi.path() + "/" + "Media";
  ui.destinationEdit->setText(destinationDir);
}

//===========================================================================
void MediaDownloaderDialog::onBrowseDestinationButtonClick()
{
  QString dir = QFileDialog::getExistingDirectory(this, "Destination directory",
      QDir::homePath());
  if (dir.length() == 0) return;
  ui.destinationEdit->setText(dir);
}

//===========================================================================
void MediaDownloaderDialog::onStartButtonClick()
{
  ui.sourceEdit->setEnabled(!_startButtonStarts);
  ui.browseSourceButton->setEnabled(!_startButtonStarts);
  ui.destinationEdit->setEnabled(!_startButtonStarts);
  ui.browseDestinationButton->setEnabled(!_startButtonStarts);
  ui.startButton->setText(_startButtonStarts ? "Cancel" : "Start");
  if (_startButtonStarts)
  {
    ui.reportEdit->setStyleSheet("background-color:white");
    _downloader = new MediaDownloader(ui.sourceEdit->text(), ui.destinationEdit->text());
    connect(_downloader, SIGNAL(finished(bool)), this, SLOT(onWorkFinished(bool)));
    connect(_downloader, SIGNAL(log(const QString &)), ui.reportEdit, SLOT(appendPlainText(const QString&)));
    connect(ui.reportEdit, SIGNAL(textChanged()), this, SLOT(onReportChanged()));
    _downloader->start();
  }
  else
    _downloader->stop();

  _startButtonStarts = !_startButtonStarts;
}

//===========================================================================
void MediaDownloaderDialog::onWorkFinished(bool success)
{
  // Start button to initial state.
  _startButtonStarts = true;
  ui.startButton->setText("Start");

  // Indicate success if the converter was not terminated.
  if (success)
  {
    ui.reportEdit->setStyleSheet("background-color:lightgreen");
    QApplication::beep();
  }

  // Delete the old conversion object.
  delete _downloader;
  _downloader = 0;

  // Enable GUI items.
  ui.sourceEdit->setEnabled(true);
  ui.browseSourceButton->setEnabled(true);
  ui.destinationEdit->setEnabled(true);
  ui.browseDestinationButton->setEnabled(true);
  ui.startButton->setEnabled(true);
}

//===========================================================================
void MediaDownloaderDialog::onReportChanged()
{
  ui.reportEdit->ensureCursorVisible();
}

//===========================================================================
void MediaDownloaderDialog::onSourceEditChanged()
{
  QSettings settings;
  settings.setValue("mediaDownloaderDialogSource", ui.sourceEdit->text());
}

//===========================================================================
void MediaDownloaderDialog::onDestinationEditChanged()
{
  QSettings settings;
  settings.setValue("mediaDownloaderDialogDestination", ui.destinationEdit->text());
}
