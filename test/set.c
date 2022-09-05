#include <assert.h>

#include "../include/quickbit.h"

int
main () {
  uint8_t field[1 << 18] = {0};
  field[100000] = 0xfe;

  quickbit_set(field, 800000, 1);
  assert(field[100000] == 0xff);

  quickbit_set(field, 800000, 0);
  assert(field[100000] == 0xfe);
}
