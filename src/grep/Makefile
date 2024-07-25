CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: s21_grep

s21_grep: s21_grep.o parser.o dynamic_memory_functions.o
	$(CC) $(CFLAGS) s21_grep.o parser.o dynamic_memory_functions.o -o s21_grep
build: s21_grep
rebuild: clean build
s21_grep.o: s21_grep.c dynamic_memory_functions.h parser.h

parser.o: parser.c parser.h

dynamic_memory_functions.o: dynamic_memory_functions.c dynamic_memory_functions.h

test: rebuild
	sh ./test_grep/test_func_grep.sh

#supposed to run in docker
test_valgrind: rebuild
	bash ./test_grep/test_mem_grep.sh

clean:
	rm -rf s21_grep *.a *.out *.o *.gch

make_style:
	cp ../../materials/linters/.clang-format .
	clang-format -i *.c */*.c */*/*.c  *.h */*.h */*/*.h
	rm -rf .clang-format

test_style:
	cp ../../materials/linters/.clang-format .
	clang-format -n *.c */*.c */*/*.c  *.h */*.h */*/*.h
	rm -rf .clang-format
