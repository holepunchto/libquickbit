#include <assert.h>

#include "../include/quickbit.h"

#define field_len (1 << 18)

int
main () {
  int e;

  int64_t start = 16600;
  int64_t end = 65680;

  uint8_t field[field_len] = {0};

  quickbit_index_t index;
  quickbit_index_init(index, field, field_len);

  quickbit_fill(field, field_len, 1, start, end);

  e = quickbit_index_fill(index, field, field_len, 1, start, end);
  assert(e == 0);

  int64_t p;

  p = quickbit_skip_first(index, field_len, 0, 0);
  assert(p == 16512);

  p = quickbit_skip_first(index, field_len, 1, start + 128);
  assert(p == 65664);
}
