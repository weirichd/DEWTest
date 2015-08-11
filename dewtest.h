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
 * DEWTest is a very small testing library for C.  It is only required that this header file
 * be included.
 */

#ifndef __DEWTEST__INCLUDED
#define __DEWTEST__INCLUDED

#include <stdio.h>

/*******************
 *  Color Defines
 *******************/

#define __DEWTEST__RED(text) "\e[41m"#text"\e[0m"
#define __DEWTEST__GREEN(text) "\e[42m"#text"\e[0m"

/************************
 *  Source Code Output
 ************************/

#define __DEWTEST__READ__SUCCESS 1
#define __DEWTEST__READ__FAIL 0

static inline int __DEWTEST__PRINT__SOURCE__LINE(char *filename, int line)
{
	FILE *fh = fopen(filename, "r");
	if(!fh)
	{
		return __DEWTEST__READ__FAIL;	
	}	

	char buffer[256];

	for(int current_line = 0; current_line < line; current_line++)
	{
		fgets(buffer, 256, fh);
	}

	fclose(fh);
	
	printf("%s", buffer);

	return __DEWTEST__READ__SUCCESS;
}

/*******************************
 *  Internal Assert Functions
 *******************************/

#define DEW_assert_true(true_thing) __DEWTEST__ASSERT__TRUE(true_thing, __FILE__, __LINE__)
#define DEW_assert_false(false_thing) __DEWTEST__ASSERT__TRUE(!false_thing, __FILE__, __LINE__)
static inline void __DEWTEST__ASSERT__TRUE(int thing_to_be_tested, char *file, int line)
{
	printf("FILE: %s  LINE: %d\t", file, line);

	if(thing_to_be_tested)
	{
		printf(__DEWTEST__GREEN(Test Passed)"\n");
	}
	else
	{
		printf(__DEWTEST__RED(Test Failed)"\n");
		__DEWTEST__PRINT__SOURCE__LINE(file, line);
	}
}

#endif  /* __DEWTEST__INCLUDED */
