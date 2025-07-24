#include <tests/buffer.test.h>

void test_buffer(uint32_t char_len) {
	Buffer bpt;
	char string[char_len];
	char user_message[1000] = {0};
	uint8_t test_case = 0;
	uint8_t expected_allocation_count = 0;
	bool expected_validation_state = true;
	bool expected_execflowhealth = false;
	uint16_t expected_buff_size = BUFF_SIZE;
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
	
	AddCase(test_case, user_message, sizeof(char)*1000 , bpt.heap_size, bpt.heap_size, char_len, "%d", "%d", false);
	AddCase(test_case, user_message, sizeof(char)*1000 , bpt.allocation_length, bpt.allocation_length, expected_buff_size, "%d", "%d", false);
	AddCase(test_case, user_message, sizeof(char)*1000 , bpt.allocation_count, bpt.allocation_count, expected_allocation_count, "%d", "%d", false);
	AddCase(test_case, user_message, sizeof(char)*1000 , bpt.exec_flow_health, bpt.exec_flow_health, expected_execflowhealth, "%s", "%s",true);
	AddCase(test_case, user_message, sizeof(char)*1000 , bpt.validation_state, bpt.validation_state, expected_validation_state, "%s", "%s", true);
	AddCase(test_case, user_message, sizeof(char)*1000 , bpt.stack_length, bpt.stack_length, bpt.allocation_length, "%d", "%d", false);
	AddCase(test_case, user_message, sizeof(char)*1000 , bpt.filled_status, bpt.filled_status, expected_filled_status, "%s", "%s", true);

	free(bpt.str);
	bpt.str = NULL;
	return;
}
