#include <assert.h>

#include "../include/quickbit.h"

#define field_len (1 << 18)

int
main () {
  uint8_t field[field_len] = {0};

  quickbit_index_t index;
  quickbit_index_init(index, field, field_len);

  for (size_t i = 0; i < field_len; i++) {
    quickbit_set(field, field_len, i, 1);

    bool c = quickbit_index_update(index, field, field_len, i);

    // The index should update on either side of a 128 bit boundary
    assert(i % 128 == 0 || i % 128 == 127 ? c : !c);

    int64_t j = quickbit_find_first(field, field_len, 0, quickbit_skip_first(index, field_len, 1, 0));

    assert(j == i + 1);
  }
}
