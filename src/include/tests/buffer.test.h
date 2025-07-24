#ifndef BUFFER_TEST_H
#define BUFFER_TEST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <rnd/buffer.h>
#include <rnd/f_stdio.h>
#include <rnd/random.h>


typedef enum {
	i8,
	i16,
	i32,
	i64,
	u8,
	u16,
	u32,
	u64,
	c,
	f,
	d,
	b
} Type;

ResolveCase_i()

#define ResolveBool(x) (x?"true" : "false")

#define AddCase(test_case, string, stringsize, var_name, actual, expected, form_spec_actual, form_spec_expected, boolean) do {\
	printf("Case [%d] <" #var_name "> :: ", test_case);\
	test_case++;\
	if(actual == expected) {\
		printf("Passed!\n");\
	} else {\
		if(boolean){\
			snprintf(string, stringsize, "Failed! | Expected value : " form_spec_expected "| Actual Value : " form_spec_actual "\n", ResolveBool(expected), ResolveBool(actual));\
		} else {\
			snprintf(string, stringsize, "Failed! | Expected value : " form_spec_expected "| Actual Value : " form_spec_actual "\n", expected, actual);\
		}\
	}\
	printf("%s\n", string);\
} while(0)

void test_buffer(uint32_t char_len);

#endif // BUFFER_TEST_H
