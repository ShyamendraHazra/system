#ifndef F_STDIO_H
#define F_STDIO_H

#include <stdint.h>
#include <stdio.h>

#if defined(__linux__) || defined(__gnu_linux__)
#define STDSTREAM "/dev/tty"
#endif

	void wf_write(const char *str);
	void wf_read(char *str);
	uint8_t fstream_read_open(const char *filename);
	uint8_t fstream_write_open(const char *filename);
	void fstream_close(FILE *stream);
	
#endif
