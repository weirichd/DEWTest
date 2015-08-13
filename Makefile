TESTS=$(wildcard test/*test.c)
TESTS_EXE=$(TESTS:.c=)
TEST_RESULTS=$(TESTS:.c=_result.txt)

all: $(TEST_RESULTS)

test/%test: test/%test.c
	gcc -Wall $< -o $@

test/%test_result.txt: test/%test
	./$< > $@
	./$<

.PHONEY: clean
.SILENT: clean

clean:
	echo "Cleaning up"
	rm -f $(TEST_EXE)
	rm -f $(TEST_RESULTS)
