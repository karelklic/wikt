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
#ifndef LIBWIKT_DICTIONARY_H
#define LIBWIKT_DICTIONARY_H

class Format4Reader;
class MediaReader;

struct dictionary
{
  /**
   * Main language of the dictionary.
   * ISO369-3 code.
   */
  char *language;

  /**
   * Javascript code used when displaying entries in web viewer.
   * UTF-8 encoding.
   *
   * Might contain variables that must be changed to proper value:
   * "%TRANSLATIONSFOLDED%" - replace by "true" or "false"
   */
  char *javascript_template;

  /**
   * Cascading Style Sheet code used when displaying entries in
   * web viewer.
   * UTF-8 encoding.
   */
  char *css;

  /** Access to dictionary entries. */
  Format4Reader *format4_reader;

  /** Access to pictures and pronunciation audio. */
  MediaReader *media_reader;
};

extern struct dictionary *dictionary_new(const char *base_path, const char *language);

extern void dictionary_free(struct dictionary *dictionary);

#endif
