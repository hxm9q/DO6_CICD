CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: s21_cat

s21_cat: clean
	@$(CC) $(CFLAGS) s21_cat.c -o s21_cat

clean:
	@rm -f *.o s21_cat

rebuild: clean all

check-format:
	@clang-format -style=Google -n *.c
	@clang-format -style=Google -n *.h

format: 
	clang-format -style=Google -i *.c
	clang-format -style=Google -i *.h