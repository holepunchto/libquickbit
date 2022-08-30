#include <assert.h>

#include "../include/field.h"

int
main () {
  uint8_t field[1 << 18] = {0};

  field_set(field, 1000000, 1);

  field_index_t index;
  field_index_init(index, field, 1 << 18, 0);

  assert(field_index_of(field, 1 << 18, 1, 0, index) == 1000000);
  assert(field_index_of(field, 1 << 18, 1, 1000000, index) == 1000000);
  assert(field_index_of(field, 1 << 18, 1, 1000001, index) == -1);
}
