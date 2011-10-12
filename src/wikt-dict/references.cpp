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
/* This file is required by commandMidToDict. */
#include "references.h"
#include <libwikt/debug.h>
#include <QRegExp>
#include <QStringList>

static void addRef(QRegExp &ref, int refOffs, QString &content, QStringList &texts, int &baseOffset)
{
  texts.append(ref.cap(1));
  content.remove(refOffs, ref.matchedLength());
  QString label = QString("<sup id=\"cite_ref-%1\">[[#cite_note-%1|&#91;%2&#93;]]</sup>")
    .arg(baseOffset + texts.size())
    .arg(texts.size());
  content.insert(refOffs, label);
}

/// @returns 
///   Offset to last unchanged character. Returns -1 if no change was possible.
static int step(QString &content, QStringList &texts, int &baseOffset, int from)
{
  QRegExp ref("<ref ?[^>]*>(.*)</ref>");
  ref.setMinimal(true);
  QRegExp references("<references\\s*/?\\s*>", Qt::CaseInsensitive);

  int referencesOffs = references.indexIn(content, from);
  int refOffs = ref.indexIn(content, from);

  if (referencesOffs == -1)
  {
    if (refOffs == -1)
      return -1;

    addRef(ref, refOffs, content, texts, baseOffset);
    return refOffs;
  }
  else
  {
    if (refOffs != -1 && refOffs < referencesOffs)
    {
      addRef(ref, refOffs, content, texts, baseOffset);    
      return refOffs;
    }
 
    QString text = "<ul><li>Notes:</li></ul>\n<ol>\n";
    for (int i = 0; i < texts.length(); ++i)
    {
      text += QString("<li><span id=\"cite_note-%1\">[[#cite_ref-%1|^]] %2</span></li>\n")
	.arg(baseOffset + i + 1)
	.arg(texts[i]);
    }
    text += "</ol>\n";
      
    content.remove(referencesOffs, references.matchedLength());
    content.insert(referencesOffs, text);

    baseOffset += texts.length();
    texts.clear();
    return referencesOffs;
  }
}

QString handleReferences(const QString &name, QString content)
{
  QStringList texts; 
  int baseOffset = 0;

  int from = 0;
  while ((from = step(content, texts, baseOffset, from)) != -1) {}

  if (texts.length() > 0)
    cstderr(QString("Error: No <references/> found while parsing %1, but <ref> tags exist. Fix the contents!").arg(name));
  
  return content;
}
