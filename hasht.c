#include <stdlib.h>
#include <string.h>
#include "hasht.h"

// QoL

int
_probe(struct hasht* t, const char* k) { 
  uint64_t h = hash_key(k);
  unsigned int i = (unsigned int)(h & (uint64_t)(t->cap - 1));

  while (t->e[i].key != NULL) { // only examine occupied entries 
    if (t->cap <= i)
      i = 0; // wrap around

    if (strcmp(k, t->e[i].key) == 0) // found
      return i;
    i++;
  }
  return i; // not found --> next available space
}

void
_set_entry(struct hasht* t, const char* k, void* v, unsigned int* j) {
  int i = _probe(t, k);
  
  if (j != NULL && i >= *j) { // this is a new set
    (*j)++; // bump len ticker
    char *mk = malloc(strlen(k) + 1);
    strcpy(mk, k);
    t->e[i].key = (const char*)mk; // set key
  }
  t->e[i].value = v; // update value
}

// end QoL


struct hasht*
hasht_create(unsigned int cap) {
  struct hasht* t = malloc(sizeof(struct hasht));
  if (t == NULL)
    return NULL;
  t->len = 0;
  t->cap = cap;
 
  t->e = calloc(t->cap, sizeof(struct hasht_entry));
  if (t->e == NULL) { // err
    free(t); // no mem leaks ;)
    return NULL;
  }
  return t;
}

void
hasht_destroy(struct hasht* t) {
  for (unsigned int i = 0; i < t->cap; i++) {
    free((void*)t->e[i].key);
  }

  free(t->e);
  free(t);
}

void*
hasht_get(struct hasht* t, const char* k) {
  int i = _probe(t, k);
  if (t->len == i) 
    return NULL;
  return t->e[i].value;
}

int
hasht_set(struct hasht* t, const char* k, void* v) {
  if (v == NULL)
    return -1;

  if (t->cap <= t->len ) { // need more space 
    t->cap += 1; 
    struct hasht_entry* new_e = calloc(t->cap, sizeof(struct hasht_entry));
    if (new_e == NULL)
      return -1;
    
    for (unsigned int i = 0; i < t->cap - 1; i++) {
      if (t->e[i].key != NULL) // need to move
        _set_entry(t, t->e[i].key, t->e[i].value, NULL); 
    }

    free(t->e);
    t->e = new_e; 
  }
 
  _set_entry(t, k, v, &t->len);
  return 0;
}


// FIXME placeholder FNV-1a until SipHash
static uint64_t hash_key(const char* key) {
  uint64_t hash = 14695981039346656037UL;
  for (const char* c = key; *c; c++) {
    hash ^= (uint64_t)(unsigned char)(*c);
    hash *= 1099511628211UL;
  }
  return hash;
}
