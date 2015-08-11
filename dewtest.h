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
 * DEWTest is a very small testing suite for C.
 */

#ifndef __DEWTEST__INCLUDED__
#define __DEWTEST__INCLUDED__

#include <stdio.h>

/*********************
 *  Color Defines
 *********************/

#define __DEWTEST__RED(text) "\e[41m"#text"\e[0m"
#define __DEWTEST__GREEN(text) "\e[42m"#text"\e[0m"



static inline void __DEWTEST__ASSERT__TEST__(int thing_we_are_testing,
                                             char *file,
                                             int line)
{
	printf("FILE: %s  LINE: %d\t", file, line);

	if(thing_we_are_testing)
	{
		printf(__DEWTEST__GREEN(Test Passed)"\n");
	}
	else
	{
		printf(__DEWTEST__RED(Test Failed)"\n");
	}
}

#define DEW_assert_true(true_thing) __DEWTEST__ASSERT__TEST__(true_thing, __FILE__, __LINE__)
#define DEW_assert_false(false_thing) __DEWTEST__ASSERT__TEST__(!false_thing, __FILE__, __LINE__)

#endif  /* __DEWTEST__INCLUDED__ */
