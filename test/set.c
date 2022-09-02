#include <assert.h>

#include "../include/field.h"

int
main () {
  uint8_t field[1 << 18] = {0};
  field[100000] = 0xfe;

  field_set(field, 800000, 1);
  assert(field[100000] == 0xff);

  field_set(field, 800000, 0);
  assert(field[100000] == 0xfe);
}
