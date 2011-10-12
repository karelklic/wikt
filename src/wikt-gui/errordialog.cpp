/* This file is part of Wikt. -*- mode: c++; c-file-style: "wikt"; -*-
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
#include "errordialog.h"

ErrorDialog::ErrorDialog(const QString &message, const QString &file,
    const QString &function, int line, const QString &stackTrace, QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	ui.message->setText(message);
	ui.file->setText(QString("%1, line %2").arg(file).arg(line));
	ui.function->setText(function);
	ui.stackTraceEdit->setPlainText(stackTrace);

  connect(ui.ignore, SIGNAL(clicked()), this, SLOT(ignore()));
  connect(ui.ok, SIGNAL(clicked()), this, SLOT(accept()));
}

ErrorDialog::~ErrorDialog()
{

}

void ErrorDialog::ignore()
{
  emit done(Ignored);
}
