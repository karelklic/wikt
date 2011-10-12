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
#include "command.h"
#include <QTextStream>
#include <QCoreApplication>
#include <QStringList>
#include <cstdlib>

static void printUsageAndDie(const QString &name)
{
  QTextStream err(stderr, QIODevice::WriteOnly);
  err << QString("%1 - Wikt dictionary build tool").arg(name) << endl;
  err << QString("Usage:") << endl;
  err << QString("  %1 xml-to-prep <xml_file> <prep_file> <errata_dir>").arg(name) << endl;
  err << QString("  %1 prep-to-mid <prep_file> <mid_file>").arg(name) << endl;
  err << QString("  %1 download-media <mid_file> <media_dir>").arg(name) << endl;
  err << QString("  %1 resize-images <mid_file> <media_dir>").arg(name) << endl;
  err << QString("  %1 pack-media <media_dir> <media_file>").arg(name) << endl;
  err << QString("  %1 mid-to-dict <mid_file> <media_file> <dict_file>").arg(name) << endl << endl;
  err << QString("See `man wikt-dict` for more information.") << endl;
  exit(1);
}

int main(int argc, char **argv)
{
  QCoreApplication app(argc, argv);
  QStringList args(QCoreApplication::arguments());

  if (args.length() < 2)
    printUsageAndDie(args.at(0));

  const QString command = args.at(1).toLower();
  if (command == "xml-to-prep")
  {
    if (args.length() < 5)
      printUsageAndDie(args.at(0));
    commandXmlToPrep(args.at(2), args.at(3), args.at(4));
  }
  else if (command == "prep-to-mid")
  {
    QString prepFile, midFile, strFrom, strTo;
    bool showNames = false;

    foreach (const QString &arg, args)
    {
      if (arg == "--names")
        showNames = true;
      else if (arg.startsWith("-f="))
        strFrom = arg.mid(3);
      else if (arg.startsWith("--from="))
        strFrom = arg.mid(7);
      else if (arg.startsWith("-t="))
        strTo = arg.mid(3);
      else if (arg.startsWith("--to="))
        strTo = arg.mid(5);
      else if (prepFile.isNull())
        prepFile = arg;
      else if (midFile.isNull())
        midFile = arg;
      else
        printUsageAndDie(args.at(0));
    }

    if (prepFile.isNull() || midFile.isNull())
      printUsageAndDie(args.at(0));

    int from = -1;
    if (!strFrom.isNull())
    {
      bool ok = false;
      from = strFrom.toInt(&ok);
      if (!ok)
        printUsageAndDie(args.at(0));
    }

    int to = -1;
    if (!strTo.isNull())
    {
      bool ok = false;
      to = strTo.toInt(&ok);
      if (!ok)
        printUsageAndDie(args.at(0));
    }

    commandPrepToMid(prepFile, midFile, from, to, showNames);
  }
  else if (command == "download-media")
  {
  }
  else if (command == "resize-images")
  {
  }
  else if (command == "pack-media")
  {
  }
  else if (command == "mid-to-dict")
  {
    QString midFile, mediaFile, dictFile, strFrom, strTo;
    bool showNames = false;

    foreach (const QString &arg, args)
    {
      if (arg == "--names")
        showNames = true;
      else if (arg.startsWith("-f="))
        strFrom = arg.mid(3);
      else if (arg.startsWith("--from="))
        strFrom = arg.mid(7);
      else if (arg.startsWith("-t="))
        strTo = arg.mid(3);
      else if (arg.startsWith("--to="))
        strTo = arg.mid(5);
      else if (midFile.isNull())
        midFile = arg;
      else if (mediaFile.isNull())
        mediaFile = arg;
      else if (dictFile.isNull())
        dictFile = arg;
      else
        printUsageAndDie(args.at(0));
    }

    if (midFile.isNull() || mediaFile.isNull() || dictFile.isNull())
      printUsageAndDie(args.at(0));

    int from = -1;
    if (!strFrom.isNull())
    {
      bool ok = false;
      from = strFrom.toInt(&ok);
      if (!ok)
        printUsageAndDie(args.at(0));
    }

    int to = -1;
    if (!strTo.isNull())
    {
      bool ok = false;
      to = strTo.toInt(&ok);
      if (!ok)
        printUsageAndDie(args.at(0));
    }

    commandMidToDict(midFile, mediaFile, dictFile,
                     from, to, showNames);
  }
  else
    printUsageAndDie(args.at(0));

  return 0;
}
