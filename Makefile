dewtest: dewtest.c dewtest.h
	ctags -R *
	gcc -std=gnu99 -Wall dewtest.c -o dewtest
	./dewtest

clean:
	rm dewtest
