#include "ham/ham.h"
#include <stdint.h>
#include <stdio.h>

int32_t main(void) {
  ham_t h = {0};
  const char *data_word = "1011001";
  ham_init(&h, data_word);

  // answer is: 10101001110
  const char *code_word = ham_solve(&h);
  printf("data_word=%s\n"
         "code_word=%s\n",
         data_word, code_word);
  ham_free(&h);
  return 0;
}
