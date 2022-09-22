#include <assert.h>

#include "../include/quickbit.h"

#define field_len (1 << 18)

int
main () {
  uint8_t field[field_len] = {0};

  quickbit_set(field, field_len, 1000000, 1);

  quickbit_index_t index;
  quickbit_index_init(index, field, field_len);

  int64_t i;

  i = quickbit_index_of(field, field_len, 1, 0, index);
  assert(i == 1000000);

  i = quickbit_index_of(field, field_len, 1, 1000000, index);
  assert(i == 1000000);

  i = quickbit_index_of(field, field_len, 1, 1000001, index);
  assert(i == -1);

  i = quickbit_index_of(field, field_len, 1, -1, index);
  assert(i == -1);

  i = quickbit_index_of(field, 125000, 1, 0, index);
  assert(i == -1);
}
