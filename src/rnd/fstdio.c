#include <stdio.h>
#include <stdint.h>
#include <rnd/f_stdio.h>

void wf_write(const char *str) {
  FILE *ostd_out = stdout;
  freopen("files/stdf.txt", "w", stdout);
  if(stdout != NULL) {
    printf("%s\n", str);
    fclose(stdout);
  }
  
  freopen(STDSTREAM, "w", stdout);
}

void wf_read(char *str) {
  FILE *ostd_in = stdin;
  freopen("files/stdf.txt", "r", stdin);
  if(stdin != NULL) {
    scanf("%[^\n]", str);
    fclose(stdin);

  }
  freopen(STDSTREAM, "r", stdin);
}

uint8_t fstream_read_open(const char *filename) {
  freopen(filename, "r", stdin);

  if(stdin == NULL) {
    return 1;
  }
  else {
    return 0;
  }
}

uint8_t fstream_write_open(const char *filename){
  freopen(filename, "w", stdout);

  if(stdout == NULL) {
    return 1;
  }
  else {
    return 0;
  }
}

void fstream_close(FILE *stream) {
  freopen(STDSTREAM, (stream == stdin ? "r" : "w"), stream);
}
