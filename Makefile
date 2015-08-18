TESTS=$(wildcard test/*test.c)
TESTS_EXE=$(TESTS:.c=)
TEST_RESULTS=$(TESTS:.c=_result.txt)

all: $(TEST_RESULTS)

test/%test: test/%test.c test/dewtest.h
	gcc -Wall $< -o $@ -DDEWTEST_OFF

test/%test_result.txt: test/%test
	./$< > $@
	./$<

.PHONEY: clean
.SILENT: clean

clean:
	echo "Cleaning up"
	rm -f $(TEST_EXE)
	rm -f $(TEST_RESULTS)
