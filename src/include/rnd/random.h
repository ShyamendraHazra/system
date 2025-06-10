#ifndef RANDOM_H
#define RANDOM_H
	#include <stdint.h>
	uint64_t get_random();
	uint64_t random_r(uint64_t high, uint64_t low);
	uint64_t check_sequence(uint64_t high, uint64_t low, uint64_t squence_lenght, uint64_t* sequence, uint64_t );
#endif
