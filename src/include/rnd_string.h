#ifndef RND_STRING_H
#define RND_STRING_H

#include<stdint.h>
#include<stdbool.h>



void string_main();

typedef struct {
	uint8_t len;
	char ptr[256];
	bool overflow;
} string;

typedef  struct {
	uint8_t len;
	string *str;
	uint8_t curr;
} buffer;


#define Buffer(x) buffer x = {.len = 0, .str = NULL, .curr = 0}

int stringtostd(string str);
int stdtostring(string *str, char pre_char);
int buffertostd(buffer buff);
int stdtobuffer(buffer *buff);

#endif // !RND_STRING_H
