#ifndef BUFFER_TEST_H
#define BUFFER_TEST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
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


#define setFormat(x, e, a) \
    occupied += snprintf(buffer + occupied, sizeof(buffer) - occupied, \
                         "Expected: %" x ", Actual: %" x, \
                         e, a)

#define ResolveBool(x) (x?"true":"fasle")

#define ResolveFormat(type, e, a) do{\
	switch(type){\
\
		case i8:\
			setFormat(PRIi8,(int8_t)e,(int8_t)a);\
			break;\
		case i16:\
			setFormat(PRIi16,(int16_t)e,(int16_t)a);\
			break;\
		case i32:\
			setFormat(PRIi32,(int32_t)e,(int32_t)a);\
			break;\
		case i64:\
			setFormat(PRIi64,(int64_t)e,(int64_t)a);\
			break;\
		case u8:\
			setFormat(PRIu8,(uint8_t)e,(uint8_t)a);\
			break;\
		case u16:\
			setFormat(PRIu16,(uint16_t)e,(uint16_t)a);\
			break;\
		case u32:\
			setFormat(PRIu32,(uint32_t)e,(uint32_t)a);\
			break;\
		case u64:\
			setFormat(PRIu64,(uint64_t)e,(uint64_t)a);\
			break;\
		case c:\
			setFormat("c",(char)e,(char)a);\
			break;\
		case f:\
			setFormat("f",(float)e,(float)a);\
			break;\
		case d:\
			setFormat("lf",(double)e,(double)a);\
			break;\
		case b:\
			setFormat("s",ResolveBool(e),ResolveBool(a));\
			break;\
	}\
} while(0)


#define AddTest(actual, expected, type) do {\
\
	uint16_t occupied = 0;\
	char buffer[2000] = {0};\
\
	occupied += snprintf(buffer+occupied, sizeof(buffer) - occupied, "|| Test for " #actual);\
	if(type >= i8 && type <= b){\
		if(actual == expected){\
			occupied += snprintf(buffer+occupied, sizeof(buffer) - occupied, " Passed! || \n");\
		} else {\
			occupied += snprintf(buffer+occupied, sizeof(buffer) - occupied, " Failed! ");\
			ResolveFormat(type, expected, actual);\
			occupied += snprintf(buffer+occupied, sizeof(buffer) - occupied, " || \n");\
		}\
		\
	}\
	\
	printf("%s", buffer);\
} while(0)


void test_buffer(uint32_t char_len);

#endif // BUFFER_TEST_H
