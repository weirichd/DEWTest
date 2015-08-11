all: dewtest test_result.txt

dewtest: dewtest.c dewtest.h Makefile
	gcc -Wall dewtest.c -o dewtest

test_result.txt: dewtest
	./dewtest > test_result.txt
	./dewtest

clean:
	rm dewtest
