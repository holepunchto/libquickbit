#include <assert.h>

#include "../include/quickbit.h"

int
main () {
  uint8_t field[4] = {0};

  quickbit_fill(field, true, 4, 28);
  assert(field[0] == 0xf0);
  assert(field[1] == 0xff);
  assert(field[2] == 0xff);
  assert(field[3] == 0x0f);

  quickbit_fill(field, true, 0, 4);
  assert(field[0] == 0xff);

  quickbit_fill(field, false, 4, 8);
  assert(field[0] == 0x0f);
}
