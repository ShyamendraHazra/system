#include <rnd/buffer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

void buffer_initializer(Buffer *bptr) {
  bptr->str = NULL;
  bptr->heap_size = 0;
  bptr->stack_length = 0;
  bptr->allocation_length = BUFF_SIZE;
  bptr->allocation_count = 0;
  bptr->filled_status = false;
  bptr->validation_state = false;
  bptr->exec_flow_health = false;
}

void std_to_buff(Buffer *bptr) {
  buffer_initializer(bptr);

  while(true) {

    bptr->filled_status = false;
    bptr->stack_length = 0;
    
    uint16_t index = 0;

    while(index < bptr->allocation_length) {

      scanf("%s", &(bptr->stack[index]));
      bptr->stack_length = index;

      if(index == bptr->allocation_length - 1) {
        bptr->filled_status = true;
      }
      
      if(bptr->stack[index] == '\n') {
        break;
      }
      
      index++;
      
    }

    if(!bptr->stack_length) {
      break;
    }

    char* temp = bptr->str;
    bptr->str = realloc(bptr->str, (bptr->stack_length+bptr->heap_size)*sizeof(char));

    if(bptr->str == NULL) {

      printf("\n\n!!!Out of memory!!! Aborting\n\n");
      bptr->str = temp;
      bptr->exec_flow_health = true;
      break;
    }
    
    for(int stack_index = 0; stack_index < index; stack_index++) {

      bptr->str[bptr->heap_size+stack_index] = bptr->stack[stack_index];
    }

    if(bptr->allocation_length - index) {
      break;
    }

    bptr->allocation_count++;
   
  }

  if(bptr->heap_size) {
    bptr->validation_state = true;
  }
}


