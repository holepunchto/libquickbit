#include <assert.h>

#include "../include/quickbit.h"

int
main () {
  uint8_t field[1 << 18] = {0};

  quickbit_index_t index;
  quickbit_index_init(index, field, 1 << 18);

  bool c;

  c = quickbit_index_update(index, field, 1000000);
  assert(!c);

  quickbit_set(field, 1000000, 1);
  c = quickbit_index_update(index, field, 1000000);
  assert(c);

  quickbit_set(field, 1000000, 0);
  c = quickbit_index_update(index, field, 1000000);
  assert(c);
}
