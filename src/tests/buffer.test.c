#include <tests/buffer.test.h>

void test_buffer(uint32_t char_len) {
	Buffer bpt;
	char string[char_len];
	// uint8_t test_case = 0;
	bool expected_filled_status = (char_len / BUFF_SIZE) ? true : false;
	FILE *fp = NULL;

	printf("Test for %d characters :: \n", char_len);

	if((fp = fopen("files/bufferio.test", "w")) == NULL) {
		fprintf(stderr, "Failed to open file files/bufferio.test\n");
	}

	for(uint64_t i = 0; i < char_len - 1; i++) {
		string[i] = (char)random_rng(126,32);
	}
	
	string[char_len - 1] = '\n';

	fprintf(fp, "%s", string);
	fflush(fp);

	freopen("files/bufferio.test", "r", stdin);

	std_to_buff(&bpt);

	fstream_close(stdin);
	
	AddTest(bpt.heap_size, char_len, u32);
	AddTest(bpt.allocation_length, BUFF_SIZE, u16);
	AddTest(bpt.allocation_count, 0, u8);
	AddTest(bpt.exec_flow_health, false, b);
	AddTest(bpt.validation_state, true, b);
	AddTest(bpt.stack_length+1, (uint16_t)char_len, u16);
	AddTest(bpt.filled_status, expected_filled_status, b);

	free(bpt.str);
	bpt.str = NULL;
	return;
}
