#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "rnd_string.h"


void read_string();

void string_main() {


  printf("Hey Hello there!\n");
  // free(buffer->str);
}


int stringtostd(string str) {
  
  // printf("%s",str.ptr);
  for(int count = 0; count < str.len; count++) {
    printf("%c", str.ptr[count]);
  }
  return 0;
}

int stdtostring(string *str, char pre_char) {
  
  if(str->len != 0) {

    printf("Buffer String element in corrupted state\n");
  } 
    str->ptr[str->len] = pre_char;
    str->len++;
  
  char char_holder;

  while(str->len <= 255 ) {

    scanf("%c", &char_holder);

    if(char_holder == '\n') {

      break;
    } else {
      str->ptr[str->len] = char_holder;
    }

    str->len++;

  }
  str->overflow = true; 
  return 0;
}


int buffertostd(buffer buff) {
  for(int count = 0; count < buff.len; count++) {
    stringtostd(*buff.str);
  }
  return 0; 
}

int stdtobuffer(buffer *buff) {
  
  if(buff->len == 0 && buff->str != NULL) {

    printf("Buffer in a corrupted state!\n");
    
    return 1;

  } else if(buff->len > 0 && buff->str == NULL) {

    printf("Buffer in unreachable state\n");
    
    return 1;

  } 

  char pre_char;

  if(buff->len == 0) {
    buff->str = (string*)malloc(sizeof(string));
  }

  if(buff->str == NULL) {
    printf("failed to allocate memory for buffer string\n");
    return 1;
  }
  
  while(true) {
    if(buff->str->len == 255) {
      break;
    }

    scanf("%c", &pre_char);

    if(pre_char == '\n') {

      printf("\ninput terminated!\n");
      break;

    }else {

      
      if(buff->len > 0) {

        buff->str =  realloc(buff->str, buff->len*sizeof(string));
      }

      if(buff->str == NULL) {
        
        printf("Failed to reallocate memory for buffer string\n");
        return 1;
      }
      
      buff->curr = buff->str + buff->len;
      stdtostring(buff->curr, pre_char);
      buff->len++;

    }
  }

  return 0;
}

