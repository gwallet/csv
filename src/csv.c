/*
 * csv - Comma Separated Value file manipulation utility
 *
 * Copyright ⓒ2019, Guillaume Wallet <wallet.guillaume@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */
#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static bool field_selected[256];

bool csv_stream(FILE *stream) {
  int c;
  int field_index = 0;
  int char_index = 0;
  bool escaped = false;
  int first_selected_field_index;
  for (first_selected_field_index = 0; first_selected_field_index < 256; first_selected_field_index++)
    if (field_selected[first_selected_field_index]) break;

  while (true) {
    c = getc(stream);
    if (c == EOF) break;

    switch (c) {
      case ',': {
        if (!escaped) {
          field_index++;
          char_index = 0;
          if (field_selected[field_index] && field_index != first_selected_field_index) {
            putchar(c);
          }
        }
        else {
          putchar(c);
        }
      } break;
      case '"': {
        char n = getc(stream);
        if (n == '"') {
          if (field_selected[field_index]) {
            putchar(c);
            putchar(n);
            char_index+=2;
          }
        }
        else {
          ungetc(n, stream);
          if (escaped) escaped = false;
          else if (char_index == 0) escaped = true;
          if (field_selected[field_index]) {
            putchar(c);
            char_index++;
          }
        }
      } break;
      case '\n': {
        field_index = 0;
        char_index = 0;
        putchar(c);
      } break;
      default: {
        if (field_selected[field_index]) {
          putchar(c);
          char_index++;
        }
      }
    }
  }

  return true;
}

bool csv_file(char *file) {
  FILE *stream;

  if (strcmp(file, "-") == 0) {
    stream = stdin;
  }
  else {
    stream = fopen(file, "r");
    if (stream == NULL) {
      fprintf(stderr, "%s : %s\n", file, strerror(errno));
      return false;
    }
  }

  bool res = csv_stream(stream);

  if (stream != stdin) {
    fclose(stream);
  }

  return res;
}

static struct option longopts[] = {
  {"fields", required_argument, NULL, 'f'},
  {"help", no_argument, NULL, 'h'},
  {NULL, 0, NULL, 0}
};

static char * prog_name;

void usage(int exit_code) {
  printf("\
Usage: %1$s OPTION... [FILE|-]\n\
  If FILE is \"-\" or absent, read from standard input.\n\
Options:\n\
  -h,--help\tdisplay usage and exits with status 0.\n\
  -f,--fields\tselect the comma separated list of fields number to output, first is 1\n\
Example:\n\
  $> %1$s -f 3,5,8,42 file.csv\n\
", prog_name);
  exit(exit_code);
}

int main(int argc, char *argv[]) {
  bool ok;
  int optc;

  prog_name = basename(argv[0]);

  memset(field_selected, true, 256);
  while ((optc = getopt_long(argc, argv, "f:h", longopts, NULL)) != -1) {
    switch (optc) {
      case 'f': {
        memset(field_selected, false, 256);
        char *fields_spec = optarg;
        char *token = strtok(fields_spec, ",");
        while (token != NULL) {
          //  from user perspective it's 1-based, but internally it's 0-based.
          field_selected[atoi(token)-1] = true;
          token = strtok(NULL, ",");
        }
      }
      break;
      case 'h':
        usage(EXIT_SUCCESS);

      default:
        usage(EXIT_FAILURE);
    }
  }

  if (optind == argc) {
    ok = csv_file("-");
  }
  else {
    ok = csv_file(argv[optind]);
  }

  return ok
    ? EXIT_SUCCESS
    : EXIT_FAILURE;
}
