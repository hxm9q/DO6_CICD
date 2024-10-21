#ifndef SRC_CAT_S21_CAT_H
#define SRC_CAT_S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILE_ERROR "s21_cat: %s: No such file or directory\n", argv[optind]

typedef struct {
  int number_nonblank;   // b
  int show_endl;         // e
  int number_all;        // n
  int squeeze_blank;     // s
  int show_tab;          // t
  int show_nonprinting;  // v

} flags;

const struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                      {"number", 0, 0, 'n'},
                                      {"squeeze-blank", 0, 0, 's'},
                                      {0, 0, 0, 0}

};

void parser(int argc, char *argv[], flags *options);
void cat(int argc, char *argv[], flags options);

#endif