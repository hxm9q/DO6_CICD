#include "s21_cat.h"

int main(int argc, char *argv[]) {
  flags options = {0};
  parser(argc, argv, &options);
  cat(argc, argv, options);

  return 0;
}

void parser(int argc, char *argv[], flags *options) {
  int opt;
  int option_index = 0;

  while ((opt = getopt_long(argc, argv, "benstvTE", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        options->number_nonblank = 1;
        break;
      case 'e':
        options->show_endl = 1;
        options->show_nonprinting = 1;
        break;
      case 'n':
        options->number_all = 1;
        break;
      case 's':
        options->squeeze_blank = 1;
        break;
      case 't':
        options->show_tab = 1;
        options->show_nonprinting = 1;
        break;
      case 'v':
        options->show_nonprinting = 1;
        break;
      case 'T':
        options->show_tab = 1;
        break;
      case 'E':
        options->show_endl = 1;
        break;
      default:
        fprintf(stderr, "Usage: benstvTE\n");
    }
    if (options->number_nonblank == 1) {
      options->number_all = 0;
    }
  }
}

void cat(int argc, char *argv[], flags options) {
  char prev;
  int ch;
  int sq = 0;
  int line_count = 1;

  for (; optind < argc; optind++) {
    FILE *f = fopen(argv[optind], "r");
    if (f != NULL) {
      while ((ch = fgetc(f)) != EOF) {
        if (options.squeeze_blank) {  // s
          if (ch == '\n' && prev == '\n') {
            if (sq) continue;
            sq++;
          } else
            sq = 0;
        }
        if (options.number_nonblank) {  // b
          if ((prev == '\n' && ch != '\n') || line_count == 1) {
            printf("%6d\t", line_count);
            line_count++;
          }
        }
        if (options.number_all &&
            ((options.number_nonblank == 0 && prev == '\n') ||
             line_count == 1)) {  // n
          printf("%6d\t", line_count);
          line_count++;
        }
        if (options.show_endl && ch == '\n') {  // e
          putchar('$');
        }
        if (options.show_tab && ch == '\t') {  // t
          printf("^");
          ch = 'I';
        }
        if (options.show_nonprinting) {  // v
          if ((ch >= 0 && ch <= 31) && ch != '\t' && ch != '\n') {
            printf("^");
            ch = ch + 64;
          } else if (ch == 127) {
            printf("^");
            ch = ch - 64;
          }
        }
        prev = ch;
        putchar(ch);
      }
      fclose(f);
    } else {
      printf(FILE_ERROR);
    }
    line_count = 1;
  }
}