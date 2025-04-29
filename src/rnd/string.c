#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "rnd_string.h"

#define  String(x) string x = {.len = 0, .ptr = NULL, .overflow = false}

void read_string();

void string_main() {

  String(var);

  printf("Hey Hello there!\n");

}


int stringtostd(string str) {

  printf("%s",str.ptr);
  return 0;
}

int stdtostring(string *str, char pre_char) {
  
  if(str->len != 0) {

    printf("Buffer String element in corrupted state\n");
  }

  for(str->len = 1; str->len <= 255; str->len++) {

    scanf("%c", &str->ptr[str->len]);

    if(str->ptr[str->len] == '\n') {

      break;
    }
  }
  
  return 0;
}


int buffertostd(buffer buff) {
 return 0; 
}

int stdtobuffer(buffer *buff) {

  char pre_char;

  while(true) {
    scanf("%c", &pre_char);

    if(pre_char == '\n') {

      printf("\nInput Terminated!\n");
      break;
    } else {

      stdtostring(buff->buff, pre_char);
    }
  }
}

