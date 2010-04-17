/* -*- mode:c;c-file-style:"bsd";c-basic-offset:2;indent-tabs-mode:nil -*-
 * This file is part of Wikt. 
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
#include "strdup_trimmed.h"
#include "utils.h"
#include "isspace_clocale.h"

/**
 * Creates a duplicate of a string with whitespace characters
 * removed from the beginning and the end.
 */
char *strdup_trimmed(char *str)
{
  char *first = str;
  while (isspace_clocale(first[0]))
    ++first;

  if (first == '\0')
  {
    char *result = xmalloc(1);
    result[0] = '\0';
    return result;
  }

  char *last = first + 1; /* points _after_ the last valid character */
  char *loop = first + 1;
  while (*loop != '\0')
    {
      if (!isspace_clocale(*loop))
	last = loop + 1;
      ++loop;
    };

  char *result = xmalloc(last - first + 1); /* 1 == \0 terminator */
  strncpy(result, first, last - first);
  result[last - first] = '\0';
  return result;
}
