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
#ifndef XMLTOEICGENERATORDIALOG_H
#define XMLTOEICGENERATORDIALOG_H

#include <QDialog>
#include "ui_Format1ToFormat2Dialog.h"

class Format1Parser;

/// @brief
/// Displays a dialog for conversion of a dictionary file from format1 to format2.
///
/// Format1 is the XML format of data files published by Wikimedia Foundation.
/// The data files contain "pages-articles" in their names.
/// Example file that can be downloaded:
/// http://download.wikimedia.org/enwiktionary/20090203/enwiktionary-20090203-pages-articles.xml.bz2
class Format1ToFormat2Dialog : public QDialog
{
  Q_OBJECT
public:
  /// Standard constructor.
  Format1ToFormat2Dialog(QWidget *parent = 0);
  virtual ~Format1ToFormat2Dialog();

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
  Ui::Format1ToFormat2DialogClass ui;
  Format1Parser *_parser;

  /// Mode of the start button.
  bool _startButtonStarts;
};

#endif // XMLTOEICGENERATORDIALOG_H
