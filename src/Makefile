UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	LCOV= lcov
	GENHTML= genhtml 
	LFLAG= -lm -lrt -lpthread -lsubunit
endif
ifeq ($(UNAME), Darwin)
	PATH := $(PATH):${HOME}/homebrew/bin
	LCOV= $(shell PATH=$(PATH) which lcov)
	GENHTML= $(shell PATH=$(PATH) which genhtml) 
	LFLAG=
endif
CC=gcc
CFLAG=  -Wall -Wextra -Werror -std=c11 -pedantic
DEBUG=
#DEBUG:= -D DEBUG
SOURCE:=$(shell find . -maxdepth 2 -name "s21_*.c")
OBJECTS:=$(SOURCE:.c=.o)
RESULT= s21_decimal.a
DIR = s21_decimal s21_big_decimal

all: $(RESULT) test gcov_report

clean:
	rm -rf $(OBJECTS) $(RESULT) test report *.gc* *.out *.gch log.txt gcov* cov

$(OBJECTS): %.o: %.c
	$(CC) $(DEBUG) $(CFLAGS) -c $(CFLAGS) $< -o $@ 

$(RESULT): $(OBJECTS)
	ar rc $@ $^
	ranlib $@
	rm -rf *.o *.gch

test: $(RESULT)
	$(CC) $(DEBUG) $(CFLAGS) tests/*.c -o $@ $^ -lcheck $(LFLAG)
	./$@

gcov_report: clean
	mkdir -p cov
	$(CC) $(DEBUG) $(SOURCE) tests/*.c -lcheck -o $@ --coverage $(LFLAG)
	./$@
	rm -rf *test*.gc*
	gcov -d . s21_*.c 
	$(LCOV) -d . -o cov/$@.info -c
	$(GENHTML) -o cov/report cov/$@.info
	open cov/report/index.html
	mv *.gc* cov

leak_style: test
	leaks -atExit -- ./test
	make clean
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(SOURCE) ./tests/*
	rm -rf .clang-format

valgrind: test
	valgrind --log-fd=1 --leak-check=full --log-file=log.txt -s ./test

main: $(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) main.c -o $@ $(LFLAG)
	./$@