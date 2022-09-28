#include <assert.h>
#include <stdio.h>

#include "../include/quickbit.h"

#define field_len (1 << 18)

int
main () {
  uint8_t field[field_len] = {0};

  quickbit_index_t index;
  quickbit_index_init(index, field, field_len);

  int64_t p;

  p = quickbit_skip_forward(index, field_len, 0, 0);
  assert(p == field_len * 8 - 1);
}
