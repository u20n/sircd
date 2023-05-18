#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../hasht.h"

int
main(void) {
  struct hasht* ht = hasht_create(1);

  assert(ht != NULL);
 
  int* iv = (int*) malloc(sizeof(int));
  assert(iv != NULL);
  *iv = 5; 

  assert(hasht_set(ht, "ab", iv) != -1); 
  
  int* v = hasht_get(ht, "ab");
  assert(v != NULL);

  assert(*iv == *v);

  hasht_destroy(ht);

  printf("All tests passed!\n");

  return 0;
}
