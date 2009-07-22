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
#include "Format3ToFormat4Dialog.h"
#include "Format3ToFormat4Converter.h"
#include <QFileDialog>
#include <QTest>
#include <QSettings>

//===========================================================================
Format3ToFormat4Dialog::Format3ToFormat4Dialog(QWidget *parent)
    : QDialog(parent), _converter(0), _startButtonStarts(true)
{
	ui.setupUi(this);

	// Set file paths from application settings.
	QSettings settings;
  ui.sourceEdit->setText(settings.value("format3toFormat4DialogSource", "").toString());
  ui.sourceMediaEdit->setText(settings.value("format3toFormat4DialogSourceMedia", "").toString());
  ui.destinationEdit->setText(settings.value("format3toFormat4DialogDestination", "").toString());

  // Connect signals and slots
  connect(ui.browseSourceButton, SIGNAL(clicked()), this, SLOT(onBrowseSourceButtonClick()));
  connect(ui.browseSourceMediaButton, SIGNAL(clicked()), this, SLOT(onBrowseSourceMediaButtonClick()));
  connect(ui.browseDestinationButton, SIGNAL(clicked()), this, SLOT(onBrowseDestinationButtonClick()));
  connect(ui.startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClick()));
  connect(ui.reportEdit, SIGNAL(textChanged()), this, SLOT(onReportChanged()));
  connect(ui.sourceEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onSourceEditChanged()));
  connect(ui.sourceMediaEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onSourceMediaEditChanged()));
  connect(ui.destinationEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onDestinationEditChanged()));
}

//===========================================================================
Format3ToFormat4Dialog::~Format3ToFormat4Dialog()
{
  if (_converter)
    delete _converter;
}

//===========================================================================
void Format3ToFormat4Dialog::onBrowseSourceButtonClick()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Select Format3 file", QDir::homePath(), "Format3 Files (*.ei3)");
  if (fileName.length() == 0) return;
  ui.sourceEdit->setText(fileName);

  if (ui.destinationEdit->text().length() != 0) return;
  QFileInfo fi(fileName);
  QString destinationFileName = fi.path() + "/" + fi.baseName() + ".ei4";
  ui.destinationEdit->setText(destinationFileName);
}

//===========================================================================
void Format3ToFormat4Dialog::onBrowseSourceMediaButtonClick()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Select Media file", QDir::homePath(), "Media Files (*.eim)");
  if (fileName.length() == 0) return;
  ui.sourceMediaEdit->setText(fileName);
}

//===========================================================================
void Format3ToFormat4Dialog::onBrowseDestinationButtonClick()
{
  QString fileName = QFileDialog::getSaveFileName(this, "New Format4 file",
      QDir::homePath(), "Format4 Files (*.ei4)");
  if (fileName.length() == 0) return;
  if (!fileName.endsWith(".ei4"))
    fileName.append(".ei4");
  ui.destinationEdit->setText(fileName);
}

//===========================================================================
void Format3ToFormat4Dialog::onStartButtonClick()
{
  ui.sourceEdit->setEnabled(!_startButtonStarts);
  ui.browseSourceButton->setEnabled(!_startButtonStarts);
  ui.sourceMediaEdit->setEnabled(!_startButtonStarts);
  ui.browseSourceMediaButton->setEnabled(!_startButtonStarts);
  ui.destinationEdit->setEnabled(!_startButtonStarts);
  ui.browseDestinationButton->setEnabled(!_startButtonStarts);
  ui.startButton->setText(_startButtonStarts ? "Cancel" : "Start");
  if (_startButtonStarts)
  {
    ui.reportEdit->setStyleSheet("background-color:white");
    _converter = new Format3ToFormat4Converter(ui.sourceEdit->text(),
        ui.sourceMediaEdit->text(), ui.destinationEdit->text());
    connect(_converter, SIGNAL(finished()), this, SLOT(onWorkFinished()));
    connect(_converter, SIGNAL(log(const QString &)), ui.reportEdit, SLOT(appendPlainText(const QString&)));
    _converter->start();
  }
  else
  {
    _converter->requestTermination();
    while (!_converter->isFinished())
      QTest::qSleep(200);
  }
  _startButtonStarts = !_startButtonStarts;
}

//===========================================================================
void Format3ToFormat4Dialog::onWorkFinished()
{
  // Start button to initial state.
  _startButtonStarts = true;
  ui.startButton->setText("Start");

  // Indicate success if the converter was not terminated.
  if (!_converter->terminated())
  {
    ui.reportEdit->setStyleSheet("background-color:lightgreen");
    QApplication::beep();
  }

  // Delete the old conversion object.
  delete _converter;
  _converter = 0;

  // Enable GUI items.
  ui.sourceEdit->setEnabled(true);
  ui.browseSourceButton->setEnabled(true);
  ui.sourceMediaEdit->setEnabled(true);
  ui.browseSourceMediaButton->setEnabled(true);
  ui.destinationEdit->setEnabled(true);
  ui.browseDestinationButton->setEnabled(true);
  ui.startButton->setEnabled(true);
}

//===========================================================================
void Format3ToFormat4Dialog::onReportChanged()
{
  ui.reportEdit->ensureCursorVisible();
}

//===========================================================================
void Format3ToFormat4Dialog::onSourceEditChanged()
{
  QSettings settings;
  settings.setValue("format3toFormat4DialogSource", ui.sourceEdit->text());
}

//===========================================================================
void Format3ToFormat4Dialog::onSourceMediaEditChanged()
{
  QSettings settings;
  settings.setValue("format3toFormat4DialogSourceMedia", ui.sourceMediaEdit->text());
}

//===========================================================================
void Format3ToFormat4Dialog::onDestinationEditChanged()
{
  QSettings settings;
  settings.setValue("format3toFormat4DialogDestination", ui.destinationEdit->text());
}
