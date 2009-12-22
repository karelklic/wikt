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
#include "languages.h"
#include "strdup_trimmed.h"
#include "malloc_safe.h"
#include "fclose_safe.h"
#include <assert.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct language *languages = NULL;

static struct language *language_new()
{
  struct language *lang = malloc_safe(sizeof(struct language));
  lang->iso639_1_code = NULL;
  lang->iso639_2_code = NULL;
  lang->iso639_2_b_code = NULL;
  lang->iso639_2_t_code = NULL;
  lang->iso639_3_code = NULL;
  lang->interwiki_name = NULL;
  lang->interwiki_prefix = NULL;
  lang->name = NULL;
  lang->prev = NULL;
  lang->next = NULL;
  return lang;
}

static void language_free(struct language *language)
{
  free(language->iso639_1_code);
  free(language->iso639_2_code);
  free(language->iso639_2_b_code);
  free(language->iso639_2_t_code);
  free(language->iso639_3_code);
  free(language->interwiki_name);
  free(language->interwiki_prefix);
  free(language->name);
  free(language);
}

static void language_prepend_to_languages(struct language *language)
{
  if (languages)
  {
    language->next = languages;
    assert(languages->prev == NULL);
    languages->prev = language;
    languages = language;
  }
  else
    languages = language;
}

static void read_languages_file(char *filename)
{
  FILE *fp = fopen(filename, "rb");
  if (!fp)
  {
    fprintf(stderr, "Unable to open file %s.\n", filename);
    exit(1);
  }

  char line[200];
  struct language *language = NULL;
  while (fgets(line, 200, fp) != NULL)
  {
    /* Skip comment lines. */
    if (line[0] == '#')
      continue;

    /* Skip whitespace on the beginning. */
    char *line_trimmed = line;
    while (isspace_clocale(line_trimmed[0]))
      ++line_trimmed;

    /* New language record. */
    if (0 == strncmp(line_trimmed, "---", 3))
    {
      if (language)
        language_prepend_to_languages(language);

      language = language_new();
      continue;
    }

    if (0 == strncmp(line_trimmed, "1", 1)) /* ISO 639-1 code */
    {
      language->iso639_1_code = strdup_trimmed(line_trimmed + 1);
      continue;
    }
    
    if (0 == strncmp(line_trimmed, "2b", 2))
    {
      language->iso639_2_b_code = strdup_trimmed(line_trimmed + 2);
      continue;
    }

    if (0 == strncmp(line_trimmed, "2t", 2))
    {
      language->iso639_2_t_code = strdup_trimmed(line_trimmed + 2);
      continue;
    }

    if (0 == strncmp(line_trimmed, "2", 1)) /* ISO 639-2 code */
    {
      /* If no string follows on this line, B and T variants are defined. */
      line_trimmed += 1;
      while (isspace_clocale(line_trimmed[0]))
	++line_trimmed;
      if (*line_trimmed != '\0')
        language->iso639_2_code = strdup_trimmed(line_trimmed);
      continue;
    }

    if (0 == strncmp(line_trimmed, "3", 1)) /* ISO 639-3 code */
    {
      language->iso639_3_code = strdup_trimmed(line_trimmed + 1);
      continue;
    }
    
    if (0 == strncmp(line_trimmed, "n", 1)) /* Interwiki language name */
    {
      language->interwiki_name = strdup_trimmed(line_trimmed + 1);
      continue;
    }

    if (0 == strncmp(line_trimmed, "p", 1)) /* Interwiki prefix */
    {
      language->interwiki_prefix = strdup_trimmed(line_trimmed + 1);
      continue;
    }

    fprintf(stderr, "Unknown line in languages file: %s\n", line_trimmed);
  }

  if (language)
    language_prepend_to_languages(language);

  fclose_safe(fp);
}

static void read_language_strings_file(FILE *fp)
{
  assert(fp);
  char line[200];
  /* Read the file line-by-line. */
  while (fgets(line, 200, fp) != NULL)
  {
    /* Skip comment lines. */
    if (line[0] == '#')
      continue;

    /* Skip whitespace on the beginning. */
    char *line_trimmed = line;
    while (isspace_clocale(line_trimmed[0]))
      ++line_trimmed;

    /* Skip empty lines. */
    if (line_trimmed[0] == '\0')
      continue;

    /* Read the ISO 639-3 code. */
    char code[4];
    strncpy(code, line_trimmed, 3);
    code[3] = '\0';

    /* Find the language. */
    struct language *lang = language_from_iso_639_3_code(code);  
    if (lang)
    {
      if (lang->name)
      {
        fprintf(stderr, "Error: name of language set to \"%s\", "
                "expecting empty name", lang->name);
        free(lang->name);
      }
      else
        lang->name = strdup_trimmed(line_trimmed + 3); /* 3 == iso code */
    }
    else
    {
      fprintf(stderr, "Error: unknown language \"%s\" found in "
              "file with language names", code);
    }
  }
}

void languages_init()
{
  read_languages_file(DATADIR "/languages/languages");

  /* Read locale-specific texts. */
  FILE *fp = fopen(DATADIR "/languages/languages_en", "r");
  if (fp)
  {
    read_language_strings_file(fp);
    fclose(fp);
  }

  /* Warn about missing localization. */
  struct language *lang = languages;
  while (lang)
  {
    if (!lang->name)
    {
      fprintf(stderr, "Error: missing localized name of language "
              "with ISO 639-3 code \"%s\"\n", lang->iso639_3_code);
    }

    lang = lang->next;
  }
}

void languages_shutdown()
{
  /* Delete all languages in the list. */
  while (languages)
  {
    struct language *next = languages->next;
    language_free(languages);
    languages = next;
  }
}

struct language *language_from_code(const char *code)
{
  /* Should be optimized using a sorted code array. */
  struct language *lang = languages;
  while (lang)
  {
    if ((lang->iso639_1_code && 0 == strcmp(lang->iso639_1_code, code))
        || (lang->iso639_2_code && 0 == strcmp(lang->iso639_2_code, code))
        || (lang->iso639_2_b_code && 0 == strcmp(lang->iso639_2_b_code, code))
        || (lang->iso639_2_t_code && 0 == strcmp(lang->iso639_2_t_code, code))
        || (lang->iso639_3_code && 0 == strcmp(lang->iso639_3_code, code)))
      return lang;

    lang = lang->next;
  }

  return NULL;
}

struct language *language_from_iso_639_3_code(const char *code)
{
  /* Should be optimized using a sorted code array. */
  struct language *lang = languages;
  while (lang)
  {
    if (lang->iso639_3_code 
        && 0 == strcmp(lang->iso639_3_code, code))
    {
      return lang;
    }

    lang = lang->next;
  }

  return NULL;
}
