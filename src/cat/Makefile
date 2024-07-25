CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: s21_cat
s21_cat: s21_cat.o
	$(CC) $(CFLAGS) s21_cat.o -o ./s21_cat
build: s21_cat
rebuild: clean build
s21_cat.o: s21_cat.c

test: rebuild
	sh ./test_cat/t_cat.sh

#supposed to run in docker
test_valgrind: rebuild
	sh ./test_cat/t_cat_valgrind.sh

clean:
	rm -rf s21_cat *.a *.out *.o *.log
make_style:
	cp ../../materials/linters/.clang-format .
	clang-format -i *.c */*.c */*/*.c  *.h */*.h */*/*.h
	rm -rf .clang-format

test_style:
	cp ../../materials/linters/.clang-format .
	clang-format -n *.c */*.c */*/*.c  *.h */*.h */*/*.h
	rm -rf .clang-format
