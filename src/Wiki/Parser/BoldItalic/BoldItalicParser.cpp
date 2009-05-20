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
#include "BoldItalicParser.h"
#include "../TextBlock/TextBlockParser.h"

struct AposToken
{
  AposToken(int offs, int aposCount) : _offs(offs), _aposCount(aposCount) {}
  int _offs;
  int _aposCount;
};

//===========================================================================
Node *BoldItalicParser::parse(Buffer &buffer)
{
  if (buffer.endOfFile()) return 0;
  // To make it faster for the most common case.
  if (buffer.nextChar() != '\'') return 0;
  QString line = buffer.nextLine();
  if (!line.startsWith("''")) return 0;

  QList<AposToken> tokens;
  QRegExp aposExp("''+");
  int offs = 0;
  while ((offs = aposExp.indexIn(line, offs)) != -1)
  {
    tokens.append(AposToken(offs, aposExp.matchedLength()));
    offs += aposExp.matchedLength();
  }

  // If there are more than 5 apostrophes in a row, assume they are all text
  // except for the last 5. Source: mediawiki-1.14.0 Parser.php
  if (tokens[0]._aposCount > 5) return 0;
  for (int i = 0; i < tokens.size(); ++i)
  {
    if (tokens[i]._aposCount > 5)
    {
      tokens[i]._offs += tokens[i]._aposCount - 5;
      tokens[i]._aposCount = 5;
    }
  }

  // If there are ever four apostrophes, assume the first is supposed to be
  // text, and the remaining three constitute mark-up for bold text.
  if (tokens[0]._aposCount == 4) return 0;
  for (int i = 0; i < tokens.size(); ++i)
  {
    if (tokens[i]._aposCount == 4)
    {
      tokens[i]._offs += 1;
      tokens[i]._aposCount -= 1;
    }
  }

  // Two apostrophes -> italics.
  // Three -> bold
  if (tokens[0]._aposCount == 2 || tokens[0]._aposCount == 3)
  {
    Node *node = 0;
    if (tokens[0]._aposCount == 2)
      node = new ItalicsNode();
    else
      node = new BoldNode();

    // Look for closing apostrophes.
    for (int i = 1; i < tokens.size(); ++i)
    {
      if (tokens[i]._aposCount == tokens[0]._aposCount)
      {
        TextBlockParser::parse(*node, line.mid(tokens[0]._aposCount,
            tokens[i]._offs - tokens[0]._aposCount));
        buffer.skip(tokens[i]._offs + tokens[i]._aposCount);
        return node;
      }
      else if (tokens[i]._aposCount == 5)
      {
        // If i is odd use the first apostrophes,
        // if it is even use the last.
        if (i % 2 == 1) // odd
        {
          TextBlockParser::parse(*node, line.mid(tokens[0]._aposCount,
              tokens[i]._offs - tokens[0]._aposCount));
          buffer.skip(tokens[i]._offs + tokens[0]._aposCount);
          return node;
        }
        else // even
        {
          TextBlockParser::parse(*node, line.mid(tokens[0]._aposCount,
              tokens[i]._offs - (2 * tokens[0]._aposCount) + tokens[i]._aposCount));
          buffer.skip(tokens[i]._offs + tokens[i]._aposCount);
          return node;
        }
      }
    }

    // no success, parse whole line
    TextBlockParser::parse(*node, line.mid(tokens[0]._aposCount));
    buffer.skip(line.length());
    return node;
  }

  if (tokens[0]._aposCount == 5)
  {
    if (tokens.size() == 1)
    {
      // parse whole line
      Node *node = new BoldNode();
      TextBlockParser::parse(*node, line.mid(3));
      buffer.skip(line.length());
      return node;
    }
    else if (tokens.size() == 2)
    {
      if (tokens[1]._aposCount == 5)
      {
        Node *node = new ItalicsNode();
        TextBlockParser::parse(*node, line.mid(2, tokens[1]._offs + 3 - 2));
        buffer.skip(tokens[1]._offs + tokens[1]._aposCount);
        return node;
      }

      // Ignore this one, and wait for next.
      return 0;
    }
    else
    {
      Node *node = 0;
      if (tokens[2]._aposCount == 2)
        node = new ItalicsNode();
      else
        node = new BoldNode();

      TextBlockParser::parse(*node, line.mid(tokens[2]._aposCount,
           tokens[2]._offs - tokens[2]._aposCount));
       buffer.skip(tokens[2]._offs + tokens[2]._aposCount);
       return node;
    }
  }

  CHECK(false);
  return 0;
}

