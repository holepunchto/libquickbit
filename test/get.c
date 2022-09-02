#include <assert.h>

#include "../include/field.h"

int
main () {
  uint8_t field[1 << 18] = {0};

  field[100000] = 0xff;
  assert(field_get(field, 800000) == 1);

  field[100000] = 0xfe;
  assert(field_get(field, 800000) == 0);
}
