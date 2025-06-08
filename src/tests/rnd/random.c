#include <bits/time.h>
#include <rnd/random.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

uint64_t get_random() {
	struct timespec tm;
	clock_gettime(CLOCK_REALTIME, &tm);
	uint64_t val = (uint64_t)tm.tv_sec << (uint64_t)tm.tv_nsec;
	val = val ^ tm.tv_sec;
	return val;
}
