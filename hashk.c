#include <stdlib.h>
#include "hasht.h"

// FIXME FNV 1a until SipHash
uint64_t*
hash(const char* str, unsigned int len) {
  uint64_t* h = malloc(64);
  *h = 14695981039346656037UL;

  for (const char* p = str; *p; p++) {
    *h ^= (uint64_t)(unsigned char)(*p);
    *h *= 1099511628211UL;
  }
  return h;
};
