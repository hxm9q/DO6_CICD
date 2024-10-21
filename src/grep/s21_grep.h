#ifndef SRC_GREP_S21_GREP_H
#define SRC_GREP_S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER 10000
#define FILE_ERROR "s21_grep: %s: No such file or directory\n", argv[optind]

typedef struct {
  int patterns;            // e
  int ignore_case;         // i
  int invert_match;        // v
  int count;               // c
  int files_with_matches;  // l
  int line_number;         // n
  int no_filename;         // h
  int no_messages;         // s
  int count_files;

} flags;

void parser(int argc, char *argv[], char search[], flags *options);
void grep(int argc, char *argv[], char search[], flags options);

void print_matching_line(char *argv[], int *stopper, int *line_counter,
                         char *line, flags options);
void print_only_count(char *argv[], int *match_count, flags options);
void print_invert_match(char *argv[], char *line, flags options);
int match(int count, int *result, regex_t preg, char *argv[], int *stopper,
          int *line_counter, char *line, flags options);

#endif