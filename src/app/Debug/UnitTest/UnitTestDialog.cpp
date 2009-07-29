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
#include "UnitTestDialog.h"
#include <QProcess>

//===========================================================================
UnitTestDialog::UnitTestDialog(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);
}

//===========================================================================
UnitTestDialog::~UnitTestDialog()
{
}

//===========================================================================
void UnitTestDialog::show()
{
  QProcess process;
  QStringList params;
  params.append("test");
  process.setWorkingDirectory(QApplication::applicationDirPath());
  process.start(QApplication::applicationFilePath(), params);
  process.waitForFinished();

  QString output = QString::fromAscii(process.readAllStandardOutput());
  ui.reportEdit->appendPlainText(output.trimmed());
  if (output.contains("FAIL!"))
  {
    ui.reportEdit->setStyleSheet("background-color:#ffcccc");
    QApplication::beep();
  }
  else
    ui.reportEdit->setStyleSheet("background-color:lightgreen");

  exec();
}
