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
 * DEWTest is a _very_ small testing library for C.  It is only required that this header file
 * be included. Access to the standard C library is required.
 *
 * Note: This has only been tested with gcc.
 */

#ifndef __DEWTEST_INCLUDED
#define __DEWTEST_INCLUDED

#ifndef DEWTEST_OFF

#include <stdio.h>  // printf
#include <ctype.h>  // isspace
#include <stdarg.h> // va_list, va_start, va_end
#include <string.h> // strstr

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

/**************************
 * Other Internal Macros
 **************************/

/* Print out a carrot at a specified position */
#define __DEWTEST_PRINT_CARROT(n) printf("%*s ^\n", n, " ")

/* Feel free to change this value before including dewtest.h */
#ifndef DEWTEST_EPSILON
#define DEWTEST_EPSILON 0.01f
#endif

#define __DEWTEST_TRUE 1
#define __DEWTEST_FALSE 0

/* Check that two values are closer than DEWTEST_EPSILON */
#define __DEWTEST_EPSILON_CLOSE(value1, value2) \
	((value1 - value2) < DEWTEST_EPSILON && (value2 - value1) < DEWTEST_EPSILON)

/************************
 *  Source Code Output
 ************************/

#define __DEWTEST_READ_SUCCESS 1
#define __DEWTEST_READ_FAIL 0

static char *__DEWTest_Remove_Leading_Whitespaces(char *string)
{
	char *string_without_whitespaces = string;

	while(string_without_whitespaces
		&& *string_without_whitespaces != '\0'
		&& isspace(*string_without_whitespaces))
	{
		++string_without_whitespaces;
	}

	return string_without_whitespaces;
}


static int __DEWTest_Print_Source_Line(char *filename, int line_number)
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

	char error_code[256];
	snprintf(error_code, 256, "%s:%d:1: %s", filename, line_number, __DEWTest_Remove_Leading_Whitespaces(buffer));
	printf("%s", error_code);

	char *carrot_pos = strstr(error_code, "(");

	__DEWTEST_PRINT_CARROT((int)(error_code - carrot_pos));

	return __DEWTEST_READ_SUCCESS;
}

/*******************
 *  Assert Macros
 *******************/


/* Fail when true_thing evaluates to false */
#define DEW_assert_true(true_thing) \
	__DEWTest_Assert(true_thing, __FILE__, __LINE__, \
	"Assert True Failed: %d\n", true_thing)

/* Fail when false_thing evaluates to true */
#define DEW_assert_false(false_thing) \
	__DEWTest_Assert(!false_thing, __FILE__, __LINE__, \
	"Assert False Failed: %d\n", false_thing)

/* Fail when equal_thing1 != equal_thing2 */
#define DEW_assert_equal(equal_thing1, equal_thing2, format_string) \
	__DEWTest_Assert(equal_thing1 == equal_thing2, __FILE__, __LINE__, \
	"Assert Equal Failed: "format_string" != "format_string"\n", equal_thing1, equal_thing2);				

/* Fail when not_equal_thing1 == not_equal_thing2 */
#define DEW_assert_not_equal(not_equal_thing1, not_equal_thing2, format_string) \
	__DEWTest_Assert(not_equal_thing1 != not_equal_thing2, __FILE__, __LINE__, \
	"Assert Not Equal Failed: "format_string" == "format_string"\n", not_equal_thing1, not_equal_thing2);				

/* Fail when close_thing1 isn't epsilon close to close_thing2 */
#define DEW_assert_close(close_thing1, close_thing2, format_string) \
	__DEWTest_Assert(__DEWTEST_EPSILON_CLOSE(close_thing1, close_thing2), __FILE__, __LINE__, \
	"Assert Close Failed: |"format_string" - "format_string"| >= %f\n", close_thing1, close_thing2, DEWTEST_EPSILON);

/************************
 * Being/End Functions
 ************************/

static void __DEWTest_Begin()
{
	
}

static void __DEWTest_End()
{

}

/*********************
 *  Assert Function
 *********************/

static int __dewtest_passed_tests = 0;
static int __dewtest_total_tests = 0;

static void __DEWTest_Assert(int thing_to_be_tested,
					char *filename,
					int line, 
					char *fail_message,
					...)
{
	if(__dewtest_total_tests == 0)
	{
		printf("TEST FILE: "__DEWTEST_BLUE_FG(%s)"\n", filename);
	}

	__dewtest_total_tests++;

	printf("Test %-4d Line %-4d " , __dewtest_total_tests, line);

	if(thing_to_be_tested)
	{
		printf(__DEWTEST_PASS"\n");
		__dewtest_passed_tests++;
	}
	else
	{
		printf(__DEWTEST_FAIL"\n");

		va_list args;
		va_start(args, fail_message);
		vprintf(fail_message, args);
		va_end(args);

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

#ifdef __GNUC__
/* If you are using gcc, this will output the results automatically */
static void DEWTest_Report_Results() __attribute__ ((destructor));
#endif

static void DEWTest_Report_Results()
{
	if(__dewtest_passed_tests == __dewtest_total_tests)
	{
		printf("Test Results: "__DEWTEST_GREEN_FG(%d / %d)" passed\n",
				__dewtest_passed_tests, __dewtest_total_tests);
	}
	else
	{
		printf("Test Results: "__DEWTEST_RED_FG(%d / %d)" passed\n",
				__dewtest_passed_tests, __dewtest_total_tests);
	}
}


#else

// Define these to be blank if they aren't being used
#define DEW_assert_true(true_thing) 
#define DEW_assert_false(false_thing) 
#define DEW_assert_equal(equal_thing1, equal_thing2, format_string) 
#define DEW_assert_not_equal(not_equal_thing1, not_equal_thing2, format_string) 
#define DEW_assert_close(close_thing1, close_thing2, format_string) 

#endif /* DEWTEST_OFF */

/*****************************
 * Undefine internal macros
 *****************************/

#undef __DEWTEST_READ_FAIL
#undef __DEWTEST_READ_SUCCESS
#undef __DEWTEST_PRINT_CARROT
#undef __DEWTEST_RED_BG
#undef __DEWTEST_GREEN_BG
#undef __DEWTEST_RED_FG
#undef __DEWTEST_GREEN_FG
#undef __DEWTEST_BLUE_FG
#undef __DEWTEST_TRUE 
#undef __DEWTEST_FALSE 

#endif  /* __DEWTEST_INCLUDED */
