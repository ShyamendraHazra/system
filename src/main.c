#include "include/rnd/f_stdio.h"
#include "include/tests/exp/file_io.h"
// #include <system.h>
// #include <rnd/random.h>
// #include <tests/rnd_string.test.h>
#include <tests/gentestfile.h>
#include <rnd/random.h>
#include <rnd/f_stdio.h>
#include <stdio.h>
// #include <tests/exp/file_io.h>
// #include <stdint.h>


int main() {
  char str[100];
  wf_write("Hey this should be written to a file stdout! \n");
  wf_read(str);
  printf("%s\n", str);
  fstream_write_open("logfile.txt");
  printf("This one should be inside a file and not stdout::%s",str);
  fstream_close(stdout);
  printf("This mssgae should be visible on the console and not in a file!\n");
  return 0;
}
