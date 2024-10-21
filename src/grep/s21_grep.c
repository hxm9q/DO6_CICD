#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char search[2 * BUFFER];  //строка поиска
  flags options = {0};
  parser(argc, argv, search, &options);
  grep(argc, argv, search, options);

  return 0;
}

void parser(int argc, char *argv[], char search[], flags *options) {
  int opt;
  while ((opt = getopt_long(argc, argv, "e:ivclnhs", 0, 0)) != -1) {
    switch (opt) {
      case 'e':
        options->patterns = 1;
        if (!search[0]) {
          strcat(search, optarg);
        } else {
          strcat(search, "|");
          strcat(search, optarg);
        }
        break;
      case 'i':
        options->ignore_case = 1;
        break;
      case 'v':
        options->invert_match = 1;
        break;
      case 'c':
        options->count = 1;
        break;
      case 'l':
        options->files_with_matches = 1;
        break;
      case 'n':
        options->line_number = 1;
        break;
      case 'h':
        options->no_filename = 1;
        break;
      case 's':
        options->no_messages = 1;
        break;
      default:
        fprintf(stderr, "Usage: eivclnhsfo\n");
    }
  }
  if (options->patterns && optind + 1 < argc) {
    options->count_files = 1;
  }
  if (optind + 2 < argc) {
    options->count_files = 1;
  }
  if (options->files_with_matches) {
    options->invert_match = 0;
  }
}

void grep(int argc, char *argv[], char search[], flags options) {
  int cflags = REG_EXTENDED;  //флаги для определения типа обработки
  regex_t preg;  //указатель на область хранения буферного шаблона
  char line[BUFFER];

  int match_count = 0;
  int line_counter = 1;
  int stopper = 0;
  int result = 0;

  if (options.ignore_case) cflags = REG_ICASE;

  if (options.patterns) {
    regcomp(&preg, search, cflags);
  } else {
    regcomp(&preg, argv[optind], cflags);
    optind++;
  }

  for (; optind < argc; optind++) {
    FILE *f = fopen(argv[optind], "r");
    if (f != NULL) {
      while (fgets(line, BUFFER, f) != NULL && stopper == 0) {
        match_count = match(match_count, &result, preg, argv, &stopper,
                            &line_counter, line, options);
        line_counter++;
      }
      if (options.count) {
        print_only_count(argv, &match_count, options);
      }
      stopper = 0;
      line_counter = 1;
      fclose(f);
    }
    if (f == NULL && options.no_messages == 0) {
      printf(FILE_ERROR);
    }
  }
  regfree(&preg);
}

int match(int match_count, int *result, regex_t preg, char *argv[],
          int *stopper, int *line_counter, char *line, flags options) {
  *result =
      regexec(&preg, line, 0, NULL, 0);  // совпадение между шаблоном и строкой
  if (line[strlen(line) - 1] == '\n') {
    line[strlen(line) - 1] = '\0';  // удаляем посл. пайп
  }
  if (*result) {
    print_invert_match(argv, line, options);
  }
  if (!(*result) && options.invert_match == 0) {
    if (options.files_with_matches) {
      printf("%s\n", argv[optind]);
      *stopper = 1;
    }
    if (*stopper == 0) {
      print_matching_line(argv, stopper, line_counter, line, options);
    }
    match_count++;
  }
  if (options.invert_match && *result) {
    match_count++;
  }
  return match_count;
}

void print_matching_line(char *argv[], int *stopper, int *line_counter,
                         char *line, flags options) {
  if (options.line_number && *stopper == 0) {
    if (options.count_files) {
      printf("%s:", argv[optind]);
    }
    printf("%d:%s\n", *line_counter, line);
  }
  if (options.no_filename && !options.count) {
    printf("%s\n", line);
  }
  if (options.count_files && !options.count && !options.line_number &&
      !options.no_filename) {
    printf("%s:", argv[optind]);
  }
  if (!options.count && !options.line_number && !options.no_filename) {
    printf("%s\n", line);
  }
}

void print_only_count(char *argv[], int *match_count, flags options) {
  if (options.count_files && options.no_filename == 0) {
    printf("%s:", argv[optind]);
  }
  printf("%d\n", *match_count);
  *match_count = 0;
}

void print_invert_match(char *argv[], char *line, flags options) {
  if (options.invert_match) {
    if (options.count_files && options.count == 0) {
      printf("%s:", argv[optind]);
    }
    if (options.count == 0) {
      printf("%s\n", line);
    }
  }
}