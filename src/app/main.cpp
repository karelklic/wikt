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
#include "mainwindow.h"
#include <libwikt/version.h>
#include <QApplication>

//===========================================================================
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // Because Phonon uses D-Bus on Linux, it is necessary to give
  // the application a name. It is also used by QSettings.
  app.setApplicationName("Wikt");
  app.setApplicationVersion(WIKT_VERSION);
  app.setOrganizationName("Wikt Community");
  app.setOrganizationDomain("wikt.org");

  MainWindow mainWin;
  // Initialize the main window and enter the main application loop.
  mainWin.show();
  return app.exec();
}
