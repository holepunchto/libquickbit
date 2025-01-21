#include <assert.h>

#include "../include/quickbit.h"

#define field_len (1 << 18)

int
main() {
  int e;

  int64_t start = 16384;
  int64_t end = 65536;

  uint8_t field[field_len] = {0};

  quickbit_index_t index;
  quickbit_index_init(index, field, field_len);

  for (size_t i = 0, n = field_len * 8; i < n; i++) {
    assert(quickbit_index_is(index, i, 0) == true);
    assert(quickbit_index_is(index, i, 1) == false);
  }

  quickbit_set(field, field_len, start, 1);
  quickbit_index_update(index, field, field_len, start);

  assert(quickbit_index_is(index, start, 0) == false);
  assert(quickbit_index_is(index, start, 1) == false);

  quickbit_fill(field, field_len, 1, start, end);
  e = quickbit_index_fill(index, field, field_len, 1, start, end);
  assert(e == 0);

  for (size_t i = start, n = end; i < n; i++) {
    assert(quickbit_index_is(index, i, 0) == false);
    assert(quickbit_index_is(index, i, 1) == true);
  }
}
