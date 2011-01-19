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

#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

#include <stdbool.h>
#include <stddef.h> /* size_t */

#define _GNU_SOURCE
#include <getopt.h> /* getopt_long, ... */

#ifdef __cplusplus
extern "C" {
#endif

struct arguments_option
{
  char *cat;
  int short_opt;
  char *long_opt;
  int has_arg;
  char *arg_name;
  char *desc;
};

struct arguments_definition
{
  void (*print_usage_header)(const char *command);
  bool (*process_option)(struct arguments_definition *def, 
			 int opt, 
			 const char *optarg, 
			 int argc, 
			 char *argv[]);
  bool (*process_non_options)(struct arguments_definition *def,
			      int optind,
			      int argc, 
			      char *argv[]);

  struct arguments_option *options;
  void *user_data;
};

bool get_arguments (struct arguments_definition *def, 
		    int argc, 
		    char *argv[]);

void print_usage (struct arguments_definition *def, 
		  const char *command);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __ARGUMENTS_H__ */
