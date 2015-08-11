all: dewtest test

dewtest: dewtest.c dewtest.h
	gcc -Wall dewtest.c -o dewtest

test: dewtest
	./dewtest

clean:
	rm dewtest
