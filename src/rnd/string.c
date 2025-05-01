#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "rnd_string.h"


void read_string();

void string_main() {


  printf("Hey Hello there!\n");

}


int stringtostd(string str) {

  printf("%s",str.ptr);
  return 0;
}

int stdtostring(string *str, char pre_char) {
  
  if(str->len != 0) {

    printf("Buffer String element in corrupted state\n");
  } else {
    str->ptr[str->len] = pre_char;
    str->len++;
  }
  
  char char_holder;

  while(str->len < 256 ) {

    scanf("%c", &char_holder);

    if(char_holder == '\n') {

      break;
    } else {
      str->ptr[str->len] = char_holder;
    }

    str->len++;

  }
  
  return 0;
}


int buffertostd(buffer buff) {
 return 0; 
}

int stdtobuffer(buffer *buff) {
  
  if(buff->len == 0 && buff->str != NULL) {

    printf("Buffer in a corrupted state!\n");
    exit(EXIT_FAILURE);

  } else if(buff->len > 0 && buff->str == NULL) {

    printf("Buffer in unreachable state\n");
    exit(EXIT_FAILURE);

  } else {
  
      char pre_char;

      while(true) {
        scanf("%c", &pre_char);

        if(pre_char == '\n') {

          printf("\nInput Terminated!\n");
          break;

        }else {

          stdtostring(buff->buff, pre_char);
        }
      }
  }
  return 0;
}

