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
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void *
xmalloc (size_t size)
{
  void *result = malloc (size);
  if (!result)
    {
      fprintf (stderr, "Malloc failed.\n");
      exit (1);
    }
  return result;
}

char *
xstrdup (const char *s)
{
  char *dup = strdup (s);
  if (!dup)
    {
      fprintf (stderr, "Strdup failed.\n");
      exit (1);
    }
  return dup;
}

char *
xasprintf (const char *format, ...)
{
  va_list p;
  char *result;
  int r;
  va_start (p, format);
#if 1 // GNU extension available
  r = vasprintf (&result, format, p);
#else
  va_list p2;
  va_copy (p2, p);
  r = vsnprintf (NULL, 0, format, p);
  result = xmalloc (r + 1);
  r = vsnprintf (result, r + 1, format, p2);
  va_end (p2);
#endif
  va_end (p);

  if (r < 0)
    {
      fprintf (stderr, "Xasprintf failed.\n");
      exit (1);
    }
  return result;
}

void
xfseek (FILE *stream, long offset, int whence)
{
  if (0 != fseek (stream, offset, whence))
    {
      fprintf (stderr, "Xfseek failed.\n");
      exit (1);
    }
}

long
xftell (FILE *stream)
{
  long pos = ftell (stream);
  if (pos < 0)
    {
      fprintf (stderr, "Xftell failed.\n");
      exit (1);
    }
  return pos;
}

void
xfclose (FILE *fp)
{
  if (0 != fclose (fp))
    {
      fprintf (stderr, "Xfclose failed.\n");
      exit (1);
    }
}

void
xfread (void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  if (nmemb != fread (ptr, size, nmemb, stream))
    {
      fprintf (stderr, "Xfread failed.\n");
      exit (1);
    }
}

FILE *
xfopen (const char *path, const char *mode)
{
  FILE *fp = fopen (path, mode);
  if (!fp)
    {
      fprintf (stderr, "Failed to open file %s in mode %s.", path, mode);
      exit (1);
    }
  return fp;
}
