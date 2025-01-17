#include "ham.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void ham_rbits(ham_t *h);
static void ham_expand(ham_t *h);
static void ham_rput(ham_t *h);

void ham_init(ham_t *h, const char *str) {
  assert(h != NULL);
  assert(str != NULL);

  size_t len = strlen(str);
  assert(len != 0);

  *h = (ham_t){
      .len = len,
      .flen = 0,
      .bitstr = (char *)malloc(sizeof(char) * len),
  };

  assert(h->bitstr != NULL);
  strcpy(h->bitstr, str);
}

void ham_free(ham_t *h) {
  assert(h != NULL);
  free(h->bitstr);
  h->bitstr = NULL;
  h->len = h->flen = 0;
}

static void ham_rbits(ham_t *h) {
  assert(h != NULL);
  while (((size_t)1 << h->flen) < (h->flen + h->len + 1))
    h->flen++;
  h->flen += h->len;
}

static void ham_expand(ham_t *h) {
  assert(h != NULL);
  char *bitstr = (char *)malloc(sizeof(char) * h->flen);
  assert(h->bitstr != NULL);

  for (size_t i = 0, j = 0, k = (h->flen - h->len - 1); j < h->flen;) {
    if ((size_t)(h->flen - (1 << k)) == j) {
      bitstr[j++] = 'X';
      k--;
      continue;
    }

    bitstr[j++] = h->bitstr[i++];
  }

  free(h->bitstr);
  h->bitstr = bitstr;
}

static void ham_rput(ham_t *h) {
  assert(h != NULL);
  for (size_t i = 0; i < h->flen - h->len; i++) {
    bool rbit = false;
    for (size_t j = 1; j <= h->flen; j++) {
      if ((j >> i) & 0x1) {
        rbit ^= h->bitstr[h->flen - j] == '1';
      }
    }
    h->bitstr[h->flen - (1 << i)] = rbit ? '1' : '0';
  }
}

const char *ham_solve(ham_t *h) {
  assert(h != NULL);
  ham_rbits(h);
  ham_expand(h);
  ham_rput(h);
  return h->bitstr;
}
