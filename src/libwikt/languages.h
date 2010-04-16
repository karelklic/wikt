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
#ifndef LIBWIKT_LANGUAGES_H
#define LIBWIKT_LANGUAGES_H

#ifdef __cplusplus
extern "C" {
#endif

struct language
{
  /**
   * ISO 639-1:2002, Codes for the representation of names of
   * languages - Part 1: Alpha-2 code, is the first part of
   * the ISO 639 series of international standards for language
   * codes. Part 1 covers the registration of two-letter codes.
   * There are 136 two-letter codes registered. The registered
   * codes cover the world's major languages.
   * ASCII encoding.
   */
  char *iso639_1_code;

  /**
   * ISO 639-2:1998, Codes for the representation of names of
   * languages - Part 2: Alpha-3 code, is the second part of
   * the ISO 639 standard, which lists codes for the representation
   * of the names of languages. The three-letter codes given for each
   * language in this part of the standard are referred to as
   * "Alpha-3" codes. There are 464 language codes in the list.
   *
   * While most languages are given one code by the standard,
   * twenty of the languages described have two three-letter codes.
   * ISO 639-2/B is a "bibliographic" code, which is derived
   * from the English name for the language and was a necessary
   * legacy feature.
   * ASCII encoding.
   */
  char *iso639_2_b_code;

  /**
   * A "terminological" code (ISO 639-2/T), which is derived
   * from the native name for the language.
   * In general the T codes are favored; ISO 639-3 uses ISO 639-2/T.
   * ASCII encoding.
   */
  char *iso639_2_t_code;

  /**
   * This code is mandatory and can not be NULL.
   *
   * ISO 639-3:2007, Codes for the representation of names of
   * languages - Part 3: Alpha-3 code for comprehensive coverage of
   * languages, is an international standard for language codes in
   * the ISO 639 series. The standard describes three‐letter codes
   * for identifying languages. It extends the ISO 639-2 alpha-3
   * codes with an aim to cover all known natural languages.
   * The standard was published by ISO on 2007-02-05.
   * ASCII encoding.
   */
  char *iso639_3_code;

  /**
   * Name of the language used for interwiki.
   * UTF-8 encoding.
   */
  char *interwiki_name;

  /**
   * Prefix used in URL for Wiktionary/Wikipedia in certain language.
   * UTF-8 encoding.
   */
  char *interwiki_prefix;

  /**
   * Names used to identify the language by user.
   * The name is in user's language (environment language).
   * UTF-8 encoding.
   */
  char *name;

  struct language *prev;
  struct language *next;
};

extern struct language *languages;

/**
 * Initializes language data.
 */
extern void languages_init();

/**
 * Releases all resources held by language data.
 */
extern void languages_shutdown();

/**
 * Returns language represented by certain ISO 639-3 code.
 * If the code is not known, NULL is returned.
 * @param code
 *   Language code in ASCII encoding.
 *   Examples: "eng", "ces".
 */
extern struct language *language_from_iso_639_3_code(const char *code);

/**
 * Returns language represented by certain interwiki prefix.
 * If the prefix is not known, NULL is returned.
 * @param prefix
 *   Interwiki prefix in ASCII encoding.
 *   Examples: "en", "cs", "zh-min-nan".
 */
extern struct language *language_from_interwiki_prefix(const char *prefix);

#ifdef __cplusplus
}
#endif

#endif /* LANGUAGE_H_ */
