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
#include "HtmlSyntaxHighlighter.h"
#include <iostream>

//===========================================================================
HtmlSyntaxHighlighter::HtmlSyntaxHighlighter(QTextDocument *parent)
  : QSyntaxHighlighter(parent)
{
  QStringList keywordPatterns;
  keywordPatterns << "<!DOCTYPE[^>]*>" << "</?html[^>]*>" << "</?head>"
    << "</?body>" << "</?p>" << "</?b>" << "</?i>" << "</?h[1-8][^>]*>"
    << "<a [^>]*>" << "</a>"
    << "</?ul>" << "</?ol>" << "</?li>" << "</?table[^>]*>" << "</?tr[^>]*>"
    << "</?td[^>]*>" << "</?th[^>]*>" << "</?caption[^>]*>" << "</?tbody[^>]*>";
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

  QTextCharFormat boldFormat;
  boldFormat.setFontWeight(99);
  BoundRule boldRule;
  boldRule.startExpression = QRegExp("<b>");
  boldRule.stopExpression = QRegExp("</b>");
  boldRule.format = boldFormat;
  boldRule.expressionIncluded = false;
  _boundRules.append(boldRule);

  QTextCharFormat italicsFormat;
  italicsFormat.setFontItalic(true);
  BoundRule italicsRule;
  italicsRule.startExpression = QRegExp("<i>");
  italicsRule.stopExpression = QRegExp("</i>");
  italicsRule.format = italicsFormat;
  italicsRule.expressionIncluded = false;
  _boundRules.append(italicsRule);

  QTextCharFormat h1Format;
  h1Format.setFontPointSize(20);
  h1Format.setFontWeight(QFont::Black);
  BoundRule h1Rule;
  h1Rule.startExpression = QRegExp("<h1[^>]*>");
  h1Rule.stopExpression = QRegExp("</h1>");
  h1Rule.format = h1Format;
  h1Rule.expressionIncluded = false;
  _boundRules.append(h1Rule);

  QTextCharFormat h2Format;
  h2Format.setFontPointSize(17);
  h2Format.setFontWeight(QFont::Black);
  BoundRule h2Rule;
  h2Rule.startExpression = QRegExp("<h2[^>]*>");
  h2Rule.stopExpression = QRegExp("</h2>");
  h2Rule.format = h2Format;
  h2Rule.expressionIncluded = false;
  _boundRules.append(h2Rule);

  QTextCharFormat h3Format;
  h3Format.setFontPointSize(15);
  h3Format.setFontWeight(QFont::Black);
  BoundRule h3Rule;
  h3Rule.startExpression = QRegExp("<h3[^>]*>");
  h3Rule.stopExpression = QRegExp("</h3>");
  h3Rule.format = h3Format;
  h3Rule.expressionIncluded = false;
  _boundRules.append(h3Rule);

  QTextCharFormat h4Format;
  h4Format.setFontPointSize(13);
  h4Format.setFontWeight(QFont::Black);
  BoundRule h4Rule;
  h4Rule.startExpression = QRegExp("<h4[^>]*>");
  h4Rule.stopExpression = QRegExp("</h4>");
  h4Rule.format = h4Format;
  h4Rule.expressionIncluded = false;
  _boundRules.append(h4Rule);

  QTextCharFormat h5Format;
  h5Format.setFontPointSize(12);
  h5Format.setFontWeight(QFont::Black);
  BoundRule h5Rule;
  h5Rule.startExpression = QRegExp("<h5[^>]*>");
  h5Rule.stopExpression = QRegExp("</h5>");
  h5Rule.format = h5Format;
  h5Rule.expressionIncluded = false;
  _boundRules.append(h5Rule);
}

//===========================================================================
void HtmlSyntaxHighlighter::highlightBlock(const QString &text)
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
/* Hangs up.
  setCurrentBlockState(0);
  for (int i = 0; i < boundRules.size(); ++i)
  {
    BoundRule rule = boundRules.at(i);
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
  }*/
}
