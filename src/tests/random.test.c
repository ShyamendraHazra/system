#include <rnd/random.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void test_rand_seq(uint64_t count, uint64_t low, uint64_t high, uint64_t test_index) {
	uint64_t len = high - low + 1;
	uint64_t seq_total = 0;
	seq* seqpt = (seq*)calloc(len, sizeof(seq));
	rndseq seqvar;
	initialise_rndseq(&seqvar, high, low, count, seqpt);
	check_sequence(&seqvar);
	

	printf("Test %ld :\n", test_index);
	printf("Total %ld distinc values generated\n", seqvar.seq_count);
	printf("case 1: ");
	if(seqvar.seq_count <= len) {
		printf("Successfull!\n");
	} else {
		printf("Failed!\n");
	}
	for(uint64_t it = 0; it < seqvar.seq_count; it++) {
		seq_total += seqvar.seqpt[it].count;
	}

	printf("case 2: ");
	if(seq_total == count) {
		printf("Successfull!\n");
	} else {
		printf("Failed!\n");
		printf("Seq Total : %ld | Count : %ld\n", seq_total, count);
	}
	free(seqpt);
}
