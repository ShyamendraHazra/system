#ifndef RND_BUFFER_H
#define RND_BUFFER_H
#include <stdint.h>
#include <stdbool.h>

	#define BUFF_SIZE 256
	
	typedef struct{
		char stack[BUFF_SIZE];
		char *str;
		uint32_t heap_size;
		uint16_t stack_length;
		uint16_t allocation_length;
		uint8_t allocation_count;
		bool filled_status;
		bool validation_state;
		bool exec_flow_health;
	} Buffer;


	void buffer_initializer(Buffer *bptr);
	void std_to_buff(Buffer *bptr);
#endif
