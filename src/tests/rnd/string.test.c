#include "tests/rnd_string.test.h"
#include "rnd_string.h"
#include <string.h>
#include <stdio.h>


void test_stdtobuffer() {
	Buffer(test_sample_one);
	
	char actual_sample[] = "This is a easy test!";
	printf("Enter the following text :: %s\n", actual_sample);

	stdtobuffer(&test_sample_one);
	
	if(!strcmp(actual_sample, test_sample_one.buff->ptr)) {

		printf("TEST PASSED!\n");
		
	} else {

		printf("TEST FAILED!\n");
	}

	printf("The entered text %s\n", test_sample_one.buff->ptr);
	printf("The expected text %s\n", actual_sample);
}
