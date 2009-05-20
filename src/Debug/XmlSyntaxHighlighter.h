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
#ifndef WIKT_XML_SYNTAX_HIGHLIGHTER_H
#define WIKT_XML_SYNTAX_HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QHash>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class XmlSyntaxHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT
public:
  XmlSyntaxHighlighter(QTextDocument *parent = 0);

protected:
  void highlightBlock(const QString &text);

private:
  struct SimpleRule
  {
    QRegExp pattern;
    QTextCharFormat format;
  };
  QVector<SimpleRule> _simpleRules;

  struct BoundRule
  {
    QRegExp startExpression;
    QRegExp stopExpression;
    QTextCharFormat format;
    bool expressionIncluded;
  };
  QVector<BoundRule> _boundRules;
};

#endif
