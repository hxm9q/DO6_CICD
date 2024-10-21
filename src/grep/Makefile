CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: s21_grep

s21_cat: clean
	@$(CC) $(CFLAGS) s21_grep.c -o s21_grep

clean:
	@rm -f *.o s21_grep

rebuild: clean all

check-format:
	@clang-format -style=Google -n *.c
	@clang-format -style=Google -n *.h

format: 
	clang-format -style=Google -i *.c
	clang-format -style=Google -i *.h