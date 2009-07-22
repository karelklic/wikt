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
#include "Format1ToFormat2Dialog.h"
#include "Format1Parser.h"
#include <QFileDialog>
#include <QSettings>

//===========================================================================
Format1ToFormat2Dialog::Format1ToFormat2Dialog(QWidget *parent) : QDialog(parent), _parser(0), _startButtonStarts(true)
{
	ui.setupUi(this);

  // Set file paths from application settings.
  QSettings settings;
  ui.sourceEdit->setText(settings.value("format1toFormat2DialogSource", "").toString());
  ui.errataEdit->setText(settings.value("format1toFormat2DialogErrata", "").toString());
  ui.destinationEdit->setText(settings.value("format1toFormat2DialogDestination", "").toString());

  // Connect signals and slots
  connect(ui.browseSourceButton, SIGNAL(clicked()), this, SLOT(onBrowseSourceButtonClick()));
  connect(ui.browseErrataButton, SIGNAL(clicked()), this, SLOT(onBrowseErrataButtonClick()));
  connect(ui.browseDestinationButton, SIGNAL(clicked()), this, SLOT(onBrowseDestinationButtonClick()));
  connect(ui.startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClick()));
  connect(ui.reportEdit, SIGNAL(textChanged()), this, SLOT(onReportChanged()));
  connect(ui.sourceEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onSourceEditChanged()));
  connect(ui.errataEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onErrataEditChanged()));
  connect(ui.destinationEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onDestinationEditChanged()));
}

//===========================================================================
Format1ToFormat2Dialog::~Format1ToFormat2Dialog()
{
  if (_parser)
    delete _parser;
}

//===========================================================================
void Format1ToFormat2Dialog::onBrowseSourceButtonClick()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Select Format1 (XML Wiktionary) file", QDir::homePath(), "Format1 Files (*.ei1)");
  if (fileName.length() == 0)
    return;
  ui.sourceEdit->setText(fileName);
  if (ui.destinationEdit->text().length() != 0)
    return;
  QFileInfo fi(fileName);
  ui.destinationEdit->setText(fi.path() + "/" + fi.baseName() + ".ei2");
}

//===========================================================================
void Format1ToFormat2Dialog::onBrowseErrataButtonClick()
{
  QString dir = QFileDialog::getExistingDirectory(this, "Errata directory", QDir::homePath());
  if (dir.length() == 0) return;
  ui.errataEdit->setText(dir);
}

//===========================================================================
void Format1ToFormat2Dialog::onBrowseDestinationButtonClick()
{
  QString fileName = QFileDialog::getSaveFileName(this, "New Format2 file", QDir::homePath(), "Format2 Files (*.ei2)");
  if (fileName.length() == 0)
    return;
  if (!fileName.endsWith(".ei2"))
    fileName.append(".ei2");
  ui.destinationEdit->setText(fileName);
}

//===========================================================================
void Format1ToFormat2Dialog::onStartButtonClick()
{
  ui.sourceEdit->setEnabled(!_startButtonStarts);
  ui.browseSourceButton->setEnabled(!_startButtonStarts);
  ui.errataEdit->setEnabled(!_startButtonStarts);
  ui.browseErrataButton->setEnabled(!_startButtonStarts);
  ui.destinationEdit->setEnabled(!_startButtonStarts);
  ui.browseDestinationButton->setEnabled(!_startButtonStarts);
  ui.startButton->setText(_startButtonStarts ? "Cancel" : "Start");
  if (_startButtonStarts)
  {
    ui.reportEdit->setStyleSheet("background-color:white");
    _parser = new Format1Parser(ui.sourceEdit->text(), ui.errataEdit->text(), ui.destinationEdit->text());
    connect(_parser, SIGNAL(finished()), this, SLOT(onWorkFinished()));
    connect(_parser, SIGNAL(log(const QString &)), ui.reportEdit, SLOT(appendPlainText(const QString&)));
    connect(ui.reportEdit, SIGNAL(textChanged()), this, SLOT(onReportChanged()));
    _parser->start();
  }
  else
    _parser->requestTermination();
  _startButtonStarts = !_startButtonStarts;
}

//===========================================================================
void Format1ToFormat2Dialog::onWorkFinished()
{
  _startButtonStarts = true;
  ui.startButton->setText("Start");

  // Indicate success if the parser was not terminated.
  if (!_parser->terminated())
  {
    ui.reportEdit->setStyleSheet("background-color:lightgreen");
    QApplication::beep();
  }

  delete _parser;
  _parser = 0;
  ui.sourceEdit->setEnabled(true);
  ui.browseSourceButton->setEnabled(true);
  ui.errataEdit->setEnabled(true);
  ui.browseErrataButton->setEnabled(true);
  ui.destinationEdit->setEnabled(true);
  ui.browseDestinationButton->setEnabled(true);
  ui.startButton->setEnabled(true);
}

//===========================================================================
void Format1ToFormat2Dialog::onReportChanged()
{
  ui.reportEdit->ensureCursorVisible();
}

//===========================================================================
void Format1ToFormat2Dialog::onSourceEditChanged()
{
  QSettings settings;
  settings.setValue("format1toFormat2DialogSource", ui.sourceEdit->text());
}

//===========================================================================
void Format1ToFormat2Dialog::onErrataEditChanged()
{
  QSettings settings;
  settings.setValue("format1toFormat2DialogErrata", ui.errataEdit->text());
}

//===========================================================================
void Format1ToFormat2Dialog::onDestinationEditChanged()
{
  QSettings settings;
  settings.setValue("format1toFormat2DialogDestination", ui.destinationEdit->text());
}
