#ifndef hasht_def
#include <stdint.h>

struct hasht_entry {
  const char* key;
  void* value;
};

struct hasht {
  struct hasht_entry* e;
  unsigned int cap;
  unsigned int len;
};

struct hasht* hasht_create(unsigned int cap);
void hasht_destroy(struct hasht* ht);

// it is assumed that value is always malloc'd (duh)
void* hasht_get(struct hasht* ht, const char* key);
int hasht_set(struct hasht* ht, const char* key, void* value);

static uint64_t hash_key(const char* key);

#define hasht_def
#endif
