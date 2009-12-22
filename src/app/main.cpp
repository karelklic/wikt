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
#include "mainwindow.h"
#include "coordinator.h"
#include <libwikt/version.h>
#include <libwikt/languages.h>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTextStream>
#include <QStringList>

//===========================================================================
int main(int argc, char **argv)
{
  languages_init();

  QApplication app(argc, argv);

  // Because Phonon uses D-Bus on Linux, it is necessary to give
  // the application a name. It is also used by QSettings.
  app.setApplicationName("Wikt");
  app.setApplicationVersion(WIKT_VERSION);
  app.setOrganizationName("Wikt");
  app.setOrganizationDomain("wikt.sourceforge.net");

  // Load the apropriate translations if available.
  const QString &locale = QLocale::system().name();
  const QString &trPath = QCoreApplication::applicationDirPath() + "/../share/wikt/translations";
  QTranslator translator;
  translator.load("wikt_" + locale, trPath);
  app.installTranslator(&translator);

  QTranslator qtTranslator;
  qtTranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  app.installTranslator(&qtTranslator);

  // Initialize the main window and enter the main application loop.
  MainWindow mainWin;
  mainWin.show();

  if (app.arguments().size() > 1)
    mainWin.coordinator()->textEnteredToLookup(app.arguments().last());

  return app.exec();
}
