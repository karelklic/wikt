/*
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
#include "languages.h"
#include "strdup_trimmed.h"
#include "utils.h"
#include <assert.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <ciso-codes/iso639_3.h>

void
languages_init()
{
  ciso639_3_init();
}

void
languages_shutdown()
{
  ciso639_3_shutdown();
}

struct ciso_639_3 *
language_from_interwiki_prefix(const char *prefix)
{
  /* Should be optimized using a sorted code array. */
  struct language *lang = languages;
  while (lang)
    {
      if (lang->interwiki_prefix
          && 0 == strcmp(lang->interwiki_prefix, prefix))
        {
          return lang;
        }

      lang = lang->next;
    }

  return NULL;
}
