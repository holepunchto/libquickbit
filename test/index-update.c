#include <assert.h>

#include "../include/quickbit.h"

int
main () {
  const size_t field_len = 1 << 18;
  uint8_t field[field_len] = {0};

  quickbit_index_t index;
  quickbit_index_init(index, field, field_len);

  bool c;

  c = quickbit_index_update(index, field, field_len, 1000000);
  assert(!c);

  quickbit_set(field, field_len, 1000000, 1);
  c = quickbit_index_update(index, field, field_len, 1000000);
  assert(c);

  quickbit_set(field, field_len, 1000000, 0);
  c = quickbit_index_update(index, field, field_len, 1000000);
  assert(c);
}
