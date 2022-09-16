#include <assert.h>

#include "../include/quickbit.h"

#define field_len 1 << 18

int
main () {
  uint8_t field[field_len] = {0};
  field[100000] = 0xfe;

  quickbit_set(field, field_len, 800000, 1);
  assert(field[100000] == 0xff);

  quickbit_set(field, field_len, 800000, 0);
  assert(field[100000] == 0xfe);
}
