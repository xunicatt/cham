#ifndef __HAM_H
#define __HAM_H

#include <stdio.h>

typedef struct {
  size_t len;
  size_t flen;
  char *bitstr;
} ham_t;

void ham_init(ham_t *h, const char *str);
const char *ham_solve(ham_t *h);
void ham_free(ham_t *h);

#endif
