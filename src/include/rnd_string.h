#ifndef RND_STRING_H
#define RND_STRING_H

#include<stdint.h>
#include<stdbool.h>



void string_main();

typedef struct {
	uint8_t len;
	char *ptr;
	bool overflow;
} string;

typedef  struct {
	uint8_t len;
	string *buff;
	uint8_t curr;
} buffer;



int stringtostd(string str);
int stdtostring(string *str, char pre_char);
int buffertostd(buffer buff);
int stdtobuffer(buffer *buff);

#endif // !RND_STRING_H
//
