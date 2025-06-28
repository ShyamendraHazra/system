#include <bits/time.h>
#include <rnd/random.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint64_t get_random() {
	struct timespec tm;
	uint32_t multiplier = 1664525;
	uint32_t incrementer  = 1013904223;
	uint64_t modulus = 4294967296;
	uint64_t seed = 0;
	uint64_t val = 0;

	clock_gettime(CLOCK_REALTIME, &tm);
	val = ((uint64_t)tm.tv_sec * 1000000000ULL) + (uint64_t)tm.tv_nsec;
	seed = (multiplier * val + incrementer) % modulus;

	return seed;
}


uint64_t random_rng(uint64_t high, uint64_t low) {
	uint64_t rand = get_random();
	uint64_t modulus = 4294967296;
	uint64_t range = high - low + 1;

	rand = (rand % range) + low;
	return rand;
}



	void initialise_rndseq(rndseq *rseqpt, uint64_t high, uint64_t low, uint64_t count, seq *seqpt) {
	
	(*rseqpt).high = high;
	(*rseqpt).low = low;
	(*rseqpt).count = count;
	(*rseqpt).seqpt = seqpt;
	(*rseqpt).seq_count = 0;
	printf("Intialised rndseq var\n");
	printf("Count : %ld | High : %ld | Low : %ld\n", (*rseqpt).count, (*rseqpt).high, (*rseqpt).low);
}


void check_sequence(rndseq *rseqpt) {

	uint64_t *numpool = (uint64_t*)calloc((*rseqpt).count, sizeof(uint64_t));

	for(uint64_t it  = 0; it < (*rseqpt).count; it++) {
		
		numpool[it] = random_rng((*rseqpt).high, (*rseqpt).low);

	}


	for(uint64_t it_1 = 0; it_1 < (*rseqpt).count; it_1++) {

		if(!it_1) {
			(*rseqpt).seqpt[it_1].val = numpool[it_1];
			(*rseqpt).seqpt[it_1].count = 1;
			(*rseqpt).seq_count++;
			continue;
		}
		
		uint64_t it = 0;
		for(it = 0; it < (*rseqpt).seq_count; it++) {
			
			if((*rseqpt).seqpt[it].val == numpool[it_1]) {
				
				(*rseqpt).seqpt[it].count++;
				break;

			}

		}

		if((*rseqpt).seq_count == it) {
			(*rseqpt).seqpt[(*rseqpt).seq_count].val = numpool[it_1];
			(*rseqpt).seqpt[(*rseqpt).seq_count].count = 1;
			(*rseqpt).seq_count++;
		}

	}
	
	free(numpool);
}
