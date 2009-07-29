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
#ifndef BUFFER_H_
#define BUFFER_H_

#include "../../../Prerequisites.h"

/// A buffer on the top of a string that is used for wiki text parsing.
class Buffer
{
public:
  /// Creates empty buffer.
  Buffer();
  /// Creates buffer with text. Buffer points to the beginning of the text.
  Buffer(const QString &text);

  /// Appends text to the end of the buffer.
  void append(const QString &text) { _text.append(text); }

  /// Checks if the buffer is at the end of data.
  bool endOfFile() const { return _pos >= _text.length(); }
  /// Checks if the buffer is at the end of line.
  bool endOfLine() const { return _text[_pos] == '\n'; }
  /// Position in underlying data.
  int pos() const { return _pos; }
  /// Whole string for various low-level algorithms.
  /// It is not affected by buffer's position pointer.
  const QString &text() const { return _text; }
  QString &text() { return _text; }
  /// Size of buffer in character count (not bytes).
  int size() const { return _text.length(); }

  /// Reads a character from the buffer.
  /// Does not change the buffer's position.
  QChar nextChar() const { return _text[_pos]; }
  QChar readChar() { return _text[_pos++]; }

  /// Reads the next line from the buffer.
  /// Does not change the buffer's position. Use next(n) or skip(n) to
  /// move the buffer pointer.
  /// @return
  ///   A line without the closing "\n".
  /// @see readLine
  QString nextLine() const;

  /// Reads a line from the buffer and moves the buffer's pointer
  /// after the line.
  QString readLine();

  /// Reads all remaining characters from the buffer.
  QString readAll();

  /// Reads specified amount of characters. Can read less characters
  /// if the end of the buffer is reached.
  /// @param count
  ///  The number of characters to be read.
  ///  Must be a positive number.
  QString read(int count);

  /// Moves back the position of read pointer in the buffer.
  void previous(int i = 1) { _pos -= i; }
  /// Moves forward the position of read pointer in the buffer.
  void next(int i = 1) { _pos += i; }
  /// Moves forward the position of read pointer in the buffer.
  void skip(int i = 1) { next(i); }
  /// Moves forward the position of read pointer in the buffer.
  void skipEmptyLines();

  /// Returns true if the text that will be read from the buffer
  /// is equal to the text provided. Case sensitive.
  bool startsWith(const QString &text) const;
  int indexOf(const QString &text, Qt::CaseSensitivity cs) const;

protected:
  QString _text;
  int _pos;
};

#endif /* BUFFER_H_ */
