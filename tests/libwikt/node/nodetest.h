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
#ifndef NODETEST_H
#define NODETEST_H
#include <QTest>
#include <QObject>

class NodeTest : public QObject
{
  Q_OBJECT
private slots:
  void article_generateXHtmlTableOfContents0();
  void linkTarget_language();
  void linkTarget_namespace();
  void linkTarget_project();
};

#endif
