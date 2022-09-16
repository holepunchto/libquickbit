#include <assert.h>

#include "../include/quickbit.h"

int
main () {
  const size_t field_len = 4;
  uint8_t field[field_len] = {0};

  quickbit_fill(field, field_len, true, 4, 28);
  assert(field[0] == 0xf0);
  assert(field[1] == 0xff);
  assert(field[2] == 0xff);
  assert(field[3] == 0x0f);

  quickbit_fill(field, field_len, true, 0, 4);
  assert(field[0] == 0xff);

  quickbit_fill(field, field_len, false, 4, 8);
  assert(field[0] == 0x0f);
}
