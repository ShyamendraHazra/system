#ifndef RANDOM_H
#define RANDOM_H
	#include <stdint.h>
	
	typedef struct {
		uint64_t val;
		uint64_t count;
	} seq;
	
	typedef struct {
		uint64_t high;
		uint64_t low;
		uint64_t count;
		seq *seqpt;
		uint64_t seq_count;
	} rndseq;

	uint64_t get_random(void);
	uint64_t random_rng(uint64_t high, uint64_t low);
	void check_sequence(rndseq *rseqpt);
	void initialise_rndseq(rndseq *rseqpt, uint64_t high, uint64_t low, uint64_t count, seq *seqpt);
#endif
