#include <assert.h>

#include "../include/quickbit.h"

#define field_len (1 << 18)

int
main () {
  uint8_t field[field_len] = {0};

  quickbit_set(field, field_len, 1000000, 1);

  int64_t i;

  i = quickbit_index_of(field, field_len, 1, 0, NULL);
  assert(i == 1000000);

  i = quickbit_index_of(field, field_len, 1, 1000000, NULL);
  assert(i == 1000000);

  i = quickbit_index_of(field, field_len, 1, 1000001, NULL);
  assert(i == -1);

  i = quickbit_index_of(field, field_len, 1, -1, NULL);
  assert(i == -1);

  i = quickbit_index_of(field, 125000, 1, 0, NULL);
  assert(i == -1);
}
