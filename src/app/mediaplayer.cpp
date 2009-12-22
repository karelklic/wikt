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
#include "mediaplayer.h"
#include "mainwindow.h"
#include "wikisource.h"
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <QBuffer>

//===========================================================================
MediaPlayer::MediaPlayer(QObject *parent) : QObject(parent)
{
  _audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
  _mediaObject = new Phonon::MediaObject(this);
  Phonon::createPath(_mediaObject, _audioOutput);
}

//===========================================================================
void MediaPlayer::play(const QString &fileName)
{
  if (!fileName.endsWith(".ogg", Qt::CaseInsensitive))
    return;

  QByteArray data = MainWindow::instance()->wikiSource()->media(fileName);
  QBuffer *buffer = new QBuffer();
  buffer->setData(data);
  Phonon::MediaSource source(buffer);
  source.setAutoDelete(true);
  _mediaObject->clearQueue();
  _mediaObject->setCurrentSource(source);
  _mediaObject->play();
}
