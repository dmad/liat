/* -*- mode: C; c-file-style: "gnu" -*- */
/*
 * Copyright (C) 2011 Dirk Dierckx <dirk.dierckx@gmail.com>
 *
 * This file is part of liat.
 *
 * liat is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liat.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h> /* memset */

#include "arguments.h"

struct arguments
{
  char *filename;
  unsigned int timeout; /* in seconds, 0 == no timeout */
};

static
void
_print_usage_header (const char *command)
{
  printf ("Usage: %s [OPTION]... [FILE]\n"
	  "Follows FILE.\n",
	  command);
}

static
void
_print_version ()
{
  printf ("%s %s\n"
	  "\n"
	  "Copyright 2011 by Dirk Dierckx <dirk.dierckx@gmail.com>\n"
	  "This is free software; see the source for copying conditions.\n"
	  "There is NO warranty; not even for MERCHANTABILITY of FITNESS\n"
	  "FOR A PARTICULAR PURPOSE.\n",
	  PACKAGE, VERSION);
}

static
bool
_process_option (struct arguments_definition *def,
		 int opt,
		 const char *optarg,
		 int argc,
		 char *argv[])
{
  struct arguments *args = def->user_data;
  bool go_on = true;

  switch (opt) {
  case '?': /* invalid option */
    go_on = false;
    break;
  case ':': /* invalid argument */
  case 'h':
    print_usage (def, argv[0]);
    go_on = false;
    break;
  case 'V':
    _print_version ();
    go_on = false;
    break;
  default: /* unhandled option */
    fprintf (stderr, "Unhandled option %d\n", opt);
    go_on = false;
    break;
  }

  return go_on;
}

static
bool
_process_non_options (struct arguments_definition *def,
		      int optind,
		      int argc,
		      char *argv[])
{
  struct arguments *args = def->user_data;
  bool go_on = true;

  return go_on;
}

static
bool
_get_arguments (struct arguments *args, int argc, char *argv[])
{
  struct arguments_definition def;
  struct arguments_option options[] = {
    { "Miscellaneous", 'V', "version", no_argument, NULL,
      "print version information and exit" },
    { "Miscellaneous", 'h', "help", no_argument, NULL,
      "display this help and exit" },
    { NULL, 0, NULL, 0, NULL, NULL }
  };

  memset (&def, 0, sizeof (struct arguments_definition));
  
  def.print_usage_header = &_print_usage_header;
  def.process_option = &_process_option;
  def.process_non_options = &_process_non_options;
  def.options = options;

  memset (args, 0, sizeof (struct arguments));

  def.user_data = args;

  return get_arguments (&def, argc, argv);
}

int
main (int argc, char *argv[])
{
  struct arguments args;
  
  if (_get_arguments (&args, argc, argv)) {
  }

  return 0;
}

