#include <stdio.h>
#include <rnd/buffer.h>
#include <tests/gentestfile.h>
#include <stdint.h>
#include <stdbool.h>

#define CHLEN 10

typedef struct {
	char str[CHLEN];
	uint8_t len;
} intstr;

typedef struct {
	char filename[24]; // finename string
	uint8_t len; // length of the filename string
	uint32_t c_size; //no. of chars to store inside the file
} filestruct;

void inttostr(intstr *elm, uint32_t val){
	uint8_t digits[CHLEN] = {0};

	while(val > 0) {
		digits[elm->len] = val % 10;
		val /= 10;
		elm->len++;
	}

	for(int it = 1;it <= elm->len; it++) {
		elm->str[elm->len - it] = (char)(digits[it - 1] + 48);
	}
}

void add_filename(filestruct* file) {
	intstr elm = {.str = {0}, .len = 0};

	inttostr(&elm, file->c_size);
	snprintf(file->filename, 25, "bufftest_%s_.txt", elm.str);

	for(uint8_t it = 0; it < 10;it++) {
		file[it].c_size = (BUFF_SIZE * it) + BUFF_SIZE;
		printf("file gen for %d chars in files/%s\n", file[it].c_size, file[it].filename);
	}
}


bool populate_file(FILE* fp, uint32_t len){
	if(fp == NULL) {
		printf("Null file pouinter error!\n");
		return false;
	}

	if(len == 0 || len < 0) {
		return 0;
	}

	for(uint8_t it = 0; it < len; it++) {

	}

	return true;
}

bool create_files(filestruct* file){
	char path[30] = {0};
	for(uint8_t it = 0; it < 10;it++) {
		if(snprintf(path, 30, "files/%s", file[it].filename) > 23) {
			FILE* fp = fopen(path, "w");

			if(fp == NULL) {
				printf("Failed to create file %s\n", path);
				return false;
			}

			if(populate_file(fp, file[it].c_size)) {
				printf("Failed to populate file %s\n", path);
				return false;
			}

			continue;
		}

		printf("Failed to create path data for %s\n", file[it].filename);
		return false;

	}
	return true;
}

void write_file() {
	filestruct file[10] = {0};
	add_filename(file);
	create_files(file);
}
