/*
 * dewtest.h
 */ 

/*
 * Copyright (c) 2015, David E. Weirich <weirich.david@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose
 * with or without fee is hereby granted, provided that the above copyright notice
 * and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*
 * About This File
 * 
 * DEWTest is a very small testing library for C.  It is only required that this header file
 * be included. Access to the standard C library is required.
 *
 * Note: This has only been tested with gcc.
 */

#ifndef __DEWTEST_INCLUDED
#define __DEWTEST_INCLUDED

#include <stdio.h> // for printf

/*******************
 *  Color Defines
 *******************/

#ifndef DEWTEST_NO_COLOR

#define __DEWTEST_RED_BG(text) "\e[1;41m"#text"\e[0m"
#define __DEWTEST_GREEN_BG(text) "\e[1;42m"#text"\e[0m"

#define __DEWTEST_RED_FG(text) "\e[31m"#text"\e[0m"
#define __DEWTEST_GREEN_FG(text) "\e[32m"#text"\e[0m"
#define __DEWTEST_BLUE_FG(text) "\e[34m"#text"\e[0m"

#else

#define __DEWTEST_RED_BG(text) #text
#define __DEWTEST_GREEN_BG(text) #text

#define __DEWTEST_RED_FG(text) #text
#define __DEWTEST_GREEN_FG(text) #text
#define __DEWTEST_BLUE_FG(text) #text

#endif /* DEWTEST_NO_COLOR */

#define __DEWTEST_PASS __DEWTEST_GREEN_BG([ Pass ])
#define __DEWTEST_FAIL __DEWTEST_RED_BG([ Fail ])

/************************
 *  Source Code Output
 ************************/

#define __DEWTEST_READ_SUCCESS 1
#define __DEWTEST_READ_FAIL 0

static inline int __DEWTest_Print_Source_Line(char *filename, int line_number)
{
	FILE *fh = fopen(filename, "r");
	if(!fh)
	{
		return __DEWTEST_READ_FAIL;	
	}	

	char buffer[256];
	int current_line_number;

	for(current_line_number = 0; current_line_number < line_number; current_line_number++)
	{
		fgets(buffer, 256, fh);
	}

	fclose(fh);

	printf("%s:%d:1: %s", filename, line_number, buffer);

	return __DEWTEST_READ_SUCCESS;
}

static inline char *___DEWTest_Remove_Leading_Whitespaces(char *string)
{
	char *string_without_whitespaces = string;

	return string_without_whitespaces;
}

/*******************
 *  Assert Macros
 *******************/

#define DEW_assert_true(true_thing) \
	__DEWTest_Assert(true_thing, __FILE__, __LINE__, \
	"Expected True, but recieved '"#true_thing"'")
#define DEW_assert_false(false_thing) \
	__DEWTest_Assert(!false_thing, __FILE__, __LINE__, \
	"Expected False, but recieved '"#false_thing"'")
#define DEW_assert_equal(equal_thing1, equal_thing2) \
	__DEWTest_Assert(equal_thing1 == equal_thing2, __FILE__, __LINE__, \
	"Expected that '"#equal_thing1" == "#equal_thing2"'");				

/*********************
 *  Assert Function
 *********************/

static int __dewtest_passed_tests = 0;
static int __dewtest_total_tests = 0;

static inline void __DEWTest_Assert(int thing_to_be_tested,
					char *filename,
					int line, 
					char *fail_message)
{
	if(__dewtest_total_tests == 0)
	{
		printf("FILE: "__DEWTEST_BLUE_FG(%s)"\n", filename);
	}

	__dewtest_total_tests++;

	printf("Test %-4d Line: %4d " , __dewtest_total_tests, line);

	if(thing_to_be_tested)
	{
		printf(__DEWTEST_PASS"\n");
		__dewtest_passed_tests++;
	}
	else
	{
		printf(__DEWTEST_FAIL"\n");
		printf("%s\n", fail_message);
		int _dew_print_source = __DEWTest_Print_Source_Line(filename, line);
		if(_dew_print_source == __DEWTEST_READ_FAIL)
		{
			printf(__DEWTEST_RED_FG(WARNING.)" An error occured when trying to read file %s.\n",
                               filename);
			printf("This could be caused by something really weird happening.\n");
		}	
	}
}

/*******************
 * Report Results
 *******************/

// This only works in GCC.  If you are using something else this will (probably) cause an error
void DEWTest_Report_Results() __attribute__ ((destructor));

void DEWTest_Report_Results()
{
	printf("Results: %d / %d passed\n", __dewtest_passed_tests, __dewtest_total_tests);
}


/*****************************
 * Undefine internal macros
 *****************************/

#undef __DEWTEST_READ_FAIL
#undef __DEWTEST_READ_SUCCESS

#endif  /* __DEWTEST_INCLUDED */
