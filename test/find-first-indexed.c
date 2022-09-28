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

  i = quickbit_find_first(field, field_len, 1, quickbit_skip_forward(index, field_len, 0, 0));
  assert(i == 1000000);

  i = quickbit_find_first(field, field_len, 1, quickbit_skip_forward(index, field_len, 0, 1000000));
  assert(i == 1000000);

  i = quickbit_find_first(field, field_len, 1, quickbit_skip_forward(index, field_len, 0, 1000001));
  assert(i == -1);

  i = quickbit_find_first(field, field_len, 1, quickbit_skip_forward(index, field_len, 0, -1));
  assert(i == -1);

  i = quickbit_find_first(field, 125000, 1, quickbit_skip_forward(index, field_len, 0, 0));
  assert(i == -1);
}
