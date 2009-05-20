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
#include "XmlSyntaxHighlighter.h"
#include <iostream>

//===========================================================================
XmlSyntaxHighlighter::XmlSyntaxHighlighter(QTextDocument *parent)
  : QSyntaxHighlighter(parent)
{
  QStringList keywordPatterns;
  keywordPatterns << "</?[^>]*>";
  foreach (QString pattern, keywordPatterns)
  {
    QTextCharFormat format;
    format.setForeground(Qt::darkBlue);
    format.setFontWeight(QFont::Bold);

    SimpleRule rule;
    rule.pattern = QRegExp(pattern);
    rule.format = format;
    _simpleRules.append(rule);
  }

  QTextCharFormat commentFormat;
  commentFormat.setForeground(Qt::red);
  BoundRule commentRule;
  commentRule.startExpression = QRegExp("<!--");
  commentRule.stopExpression = QRegExp("-->");
  commentRule.format = commentFormat;
  commentRule.expressionIncluded = true;
  _boundRules.append(commentRule);
}

//===========================================================================
void XmlSyntaxHighlighter::highlightBlock(const QString &text)
{
  foreach (SimpleRule rule, _simpleRules)
  {
    QRegExp expression(rule.pattern);
    int index = text.indexOf(expression);
    while (index >= 0)
    {
      int length = expression.matchedLength();
      setFormat(index, length, rule.format);
      index = text.indexOf(expression, index + length);
    }
  }

  setCurrentBlockState(0);
  for (int i = 0; i < _boundRules.size(); ++i)
  {
    BoundRule rule = _boundRules.at(i);
    int startIndex = 0;
    if (previousBlockState() <= 0 || (previousBlockState() & (1<<i)) == 0)
      startIndex = text.indexOf(rule.startExpression);

    while (startIndex >= 0)
    {
      int endIndex = text.indexOf(rule.stopExpression, startIndex);
      int length;
      if (endIndex == -1)
        setCurrentBlockState(currentBlockState() + (1<<i));


      if (rule.expressionIncluded)
      {
        if (endIndex == -1)
          length = text.length() - startIndex;
        else
          length = endIndex - startIndex + rule.stopExpression.matchedLength();
        setFormat(startIndex, length, rule.format);
      }
      else
      {
        if (endIndex == -1)
          length = text.length() - startIndex;
        else
          length = endIndex - startIndex;
        if (startIndex != 0)
        {
          length -= rule.startExpression.matchedLength();
          setFormat(startIndex + rule.startExpression.matchedLength(), length, rule.format);
        }
        else
          setFormat(startIndex, length, rule.format);
      }

      startIndex = text.indexOf(rule.startExpression, startIndex + length);
    }
  }
}
