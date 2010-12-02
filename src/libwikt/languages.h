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

#include <stdbool.h>

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
