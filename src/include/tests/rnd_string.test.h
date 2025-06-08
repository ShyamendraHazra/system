#ifndef RND_STRING_TEST_H
#define RND_STRING_TEST_H

#include <stdbool.h>

#define MAX_TEST_METHODS  1000

void call_test();
int asert_equal_i(int ideal, int result);
int asert_equal_c(char ideal, char result);
int asert_equal_f(float ideal, float result);
int asert_equal_b(bool ideal, bool result);


#endif // RND_STRING_TEST_H
