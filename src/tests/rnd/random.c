#include <bits/time.h>
#include <rnd/random.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

uint64_t get_random() {
	struct timespec tm;
	uint32_t multiplier = 1664525;
	uint32_t incrementer  = 1013904223;
	uint64_t modulus = 4294967296;
	uint64_t seed = 0;
	uint64_t val = 0;

	clock_gettime(CLOCK_REALTIME, &tm);
	val = ((uint64_t)tm.tv_sec * 1000000000ULL) << ((uint64_t)tm.tv_nsec % 1000000000ULL);
	val = val ^ tm.tv_sec;
	seed = (multiplier * val + incrementer) % modulus;

	return seed;
}


uint64_t random_r(uint64_t high, uint64_t low) {
	uint64_t rand = get_random();
	uint64_t modulus = 4294967296;
	uint64_t range = high - low + 1;

	rand = (rand % range) + low;
	return rand;
}



uint64_t check_sequence(uint64_t high, uint64_t low, uint64_t squence_lenght) {

}
