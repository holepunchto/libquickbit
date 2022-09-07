#include <assert.h>

#include "../include/quickbit.h"

int
main () {
  uint8_t field[1 << 18] = {0};

  quickbit_set(field, 1000000, 1);

  quickbit_index_t index;
  quickbit_index_init(index, field, 1 << 18);

  int64_t i;

  i = quickbit_index_of(field, 1 << 18, 1, 0, index);
  assert(i == 1000000);

  i = quickbit_index_of(field, 1 << 18, 1, 1000000, index);
  assert(i == 1000000);

  i = quickbit_index_of(field, 1 << 18, 1, 1000001, index);
  assert(i == -1);

  i = quickbit_index_of(field, 125000, 1, 0, index);
  assert(i == -1);
}
