#include <assert.h>

#include "../include/quickbit.h"

#define field_len (1 << 18)

int
main () {
  uint8_t field[field_len] = {0};

  quickbit_index_t index;
  quickbit_index_init(index, field, field_len);

  int64_t p;

  p = quickbit_skip_last(index, field_len, 0, -1);
  assert(p == 0);

  p = quickbit_skip_last(index, field_len, 1, -1);
  assert(p == field_len * 8 - 1);

  quickbit_set(field, field_len, 1000000, 1);
  quickbit_index_update(index, field, field_len, 1000000);

  p = quickbit_skip_last(index, field_len, 0, -1);
  assert(p >= 1000000);
}
