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
#include "dictionary.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

struct dictionary *
dictionary_new (const char *base_path, const char *language)
{
  struct dictionary *dictionary = (struct dictionary*) xmalloc (sizeof (struct dictionary));
  dictionary->language = xstrdup (language);

  /* Load the CSS file. */
  char *css_file_name = xasprintf ("%s%s", base_path, ".css");
  FILE *fp = xfopen (css_file_name, "rb");
  free (css_file_name);
  xfseek (fp, 0, SEEK_END);
  long size = xftell (fp);
  xfseek (fp, 0, SEEK_SET);
  dictionary->css = (char*) xmalloc (size);
  xfread (dictionary->css, size, 1, fp);
  xfclose (fp);

  return dictionary;
}

void
dictionary_free (struct dictionary *dictionary)
{
  free(dictionary->language);
  free(dictionary->css);
  free(dictionary);
}
