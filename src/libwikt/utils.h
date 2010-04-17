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
#ifndef LIBWIKT_UTILS_H
#define LIBWIKT_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>

/**
 * Allocates a block of `size` bytes of memory, returning a pointer
 * to the beginning of the block.
 * The content of the newly allocated block is not initialized.
 * @return
 *   This function does not return NULL. It calls exit() if
 *   a failure happens.
 */
extern void *xmalloc (size_t size);

/**
 * Returns a pointer to a new string which is a duplicate
 * of the string s. Memory for the new string must be freed
 * with function free.
 * @return
 *   This function does not return NULL. It calls exit() if
 *   a failure happens.
 */
extern char *xstrdup (const char *s);

/**
 * Creates a properly-sized string and prints formatted
 * output to it. The returned pointer must be freed with
 * function free.
 */
extern char *xasprintf (const char *format, ...);

/**
 * Sets the file position indicator for the stream.
 * Exits with error message instead of failure.
 */
extern void xfseek (FILE *stream, long offset, int whence);

/**
 * Exits with error message instead of failure.
 */
extern long xftell (FILE *stream);

/**
 * Exits with error message instead of failure.
 */
extern void xfclose (FILE *fp);

/**
 * Exits with error message instead of failing to read.
 */
extern void xfread (void *ptr, size_t size, size_t nmemb, FILE *stream);

/**
 * Exits with error message instead of failing to open
 * the file.
 */
extern FILE *xfopen (const char *path, const char *mode);

#ifdef __cplusplus
}
#endif

#endif
