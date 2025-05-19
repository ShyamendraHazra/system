#include "tests/rnd_string.test.h"
#include "rnd_string.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void test_stdtobuffer() {
	Buffer(test_sample_one);
	
	char actual_sample[] = "This is a easy test!";
	printf("Enter the following text :: %s\n", actual_sample);

	stdtobuffer(&test_sample_one);
	
	if(!strcmp(actual_sample, test_sample_one.str->ptr)) {

		printf("TEST PASSED!\n");
		
	} else {

		printf("TEST FAILED!\n");
	}
	
	printf("The entered text ");
	buffertostd(test_sample_one);
	printf("\nThe expected text %s\n", actual_sample);


  free(test_sample_one.str);
}

void test_stdtostring() {
	string str = {.len = 0, .ptr = 0, .overflow = false};

	char actual_sample[] = "This is a easy test!";
	char expected_sample[] = "his is a easy test!";
	printf("Enter the following text :: %s\n", expected_sample);

	stdtostring(&str, 'T');
	
	if(!strcmp(actual_sample, str.ptr)) {

		printf("TEST PASSED!\n");
		
	} else {

		printf("TEST FAILED!\n");
	}

	printf("The entered text %s\n", str.ptr);
	printf("The expected text %s\n", actual_sample);

}

void call_test() {
	void (*test_methods[MAX_TEST_METHODS])();

	uint16_t total_registered_test_count = 0;	
	
	test_methods[total_registered_test_count++] = test_stdtobuffer;
	test_methods[total_registered_test_count++] = test_stdtostring;
	

	for(int count = 0; count < total_registered_test_count; count++) {
		printf("Case %d :: ", count+1);
		test_methods[count]();
	}

	printf("Total %d tests run\n", total_registered_test_count);

}
