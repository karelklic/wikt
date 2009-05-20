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
#include "MediaPackerDialog.h"
#include "MediaPacker.h"
#include <QFileDialog>
#include <QTest>
#include <QSettings>

//===========================================================================
MediaPackerDialog::MediaPackerDialog(QWidget *parent)
  : QDialog(parent), _packer(0), _startButtonStarts(true)
{
	ui.setupUi(this);

  // Set paths from application settings.
  QSettings settings;
  ui.sourceEdit->setText(
      settings.value("mediaPackerDialogSource", "").toString());
  ui.destinationEdit->setText(
      settings.value("mediaPackerDialogDestination", "").toString());
}

//===========================================================================
MediaPackerDialog::~MediaPackerDialog()
{
  if (_packer)
    delete _packer;
}

//===========================================================================
void MediaPackerDialog::onBrowseSourceButtonClick()
{
  QString dir = QFileDialog::getExistingDirectory(this, "Source directory",
      QDir::homePath());
  if (dir.length() == 0) return;
  ui.sourceEdit->setText(dir);
}

//===========================================================================
void MediaPackerDialog::onBrowseDestinationButtonClick()
{
  QString fileName = QFileDialog::getSaveFileName(this, "New Media file",
      QDir::homePath(), "Media Files (*.eim)");
  if (fileName.length() == 0) return;
  ui.destinationEdit->setText(fileName);
}

//===========================================================================
void MediaPackerDialog::onStartButtonClick()
{
  ui.sourceEdit->setEnabled(!_startButtonStarts);
  ui.browseSourceButton->setEnabled(!_startButtonStarts);
  ui.destinationEdit->setEnabled(!_startButtonStarts);
  ui.browseDestinationButton->setEnabled(!_startButtonStarts);
  ui.startButton->setText(_startButtonStarts ? "Cancel" : "Start");
  if (_startButtonStarts)
  {
    ui.reportEdit->setStyleSheet("background-color:white");
    _packer = new MediaPacker(ui.sourceEdit->text(), ui.destinationEdit->text());
    connect(_packer, SIGNAL(finished()), this, SLOT(onWorkFinished()));
    connect(_packer, SIGNAL(log(const QString &)), ui.reportEdit, SLOT(appendPlainText(const QString&)));
    connect(ui.reportEdit, SIGNAL(textChanged()), this, SLOT(onReportChanged()));
    _packer->start();
  }
  else
  {
    _packer->requestTermination();
    while (!_packer->isFinished())
      QTest::qSleep(200);
  }

  _startButtonStarts = !_startButtonStarts;
}

//===========================================================================
void MediaPackerDialog::onWorkFinished()
{
  // Start button to initial state.
  _startButtonStarts = true;
  ui.startButton->setText("Start");

  // Indicate success if the packer was not terminated.
  if (!_packer->terminated())
  {
    ui.reportEdit->setStyleSheet("background-color:lightgreen");
    QApplication::beep();
  }

  // Delete the old conversion object.
  delete _packer;
  _packer = 0;

  // Enable GUI items.
  ui.sourceEdit->setEnabled(true);
  ui.browseSourceButton->setEnabled(true);
  ui.destinationEdit->setEnabled(true);
  ui.browseDestinationButton->setEnabled(true);
  ui.startButton->setEnabled(true);
}

//===========================================================================
void MediaPackerDialog::onReportChanged()
{
  ui.reportEdit->ensureCursorVisible();
}

//===========================================================================
void MediaPackerDialog::onSourceEditChanged()
{
  QSettings settings;
  settings.setValue("mediaPackerDialogSource", ui.sourceEdit->text());
}

//===========================================================================
void MediaPackerDialog::onDestinationEditChanged()
{
  QSettings settings;
  settings.setValue("mediaPackerDialogDestination", ui.destinationEdit->text());
}
