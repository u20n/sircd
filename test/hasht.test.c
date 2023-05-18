#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hasht.h"

int
main(void) {
  struct hasht* ht = hasht_create(1);

  if (ht == NULL)
    printf("could not make hasht\n");
  
  int* iv = (int*) malloc(sizeof(int));
  assert(iv != NULL);
  *iv = 5; 

  if ( hasht_set(ht, "ab", iv) == -1 )
    printf("could not set\n");
  
  int* v = hasht_get(ht, "ab");
  if ( v == NULL )
    printf("could not get\n");

  printf("set %s, got %d\n", "ab", *v);

  hasht_destroy(ht);
  return 0;
}
