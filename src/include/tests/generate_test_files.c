#include <stdio.h>
// #include <rnd/buffer.h>
#include <tests/gentestfile.h>
#include <stdint.h>
#define CHLEN 10
static char filenames[10][24] = {0};
static uint8_t fl_ind = 0;
typedef struct {
	char str[CHLEN];
	uint8_t len;
} intstr;

typedef struct {
	char filename[24];
	uint8_t fill;
	uint32_t count;
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

void add_filename(uint32_t size) {
	intstr elm = {.str = {0}, .len = 0};
	inttostr(&elm, size);
	for(int it = 0; it < elm.len; it++){
		printf("ind[%d] => %c\n", it+1, elm.str[it]);
	}
	printf("The whole string is :: %s",elm.str);
	

}

void write_file() {
	add_filename(112344);


}
