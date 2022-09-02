#include <assert.h>

#include "../include/field.h"

int
main () {
  uint8_t field[1 << 18] = {0};

  field_index_t index;
  field_index_init(index, field, 1 << 18);

  bool c;

  c = field_index_update(index, field, 1000000);
  assert(!c);

  field_set(field, 1000000, 1);
  c = field_index_update(index, field, 1000000);
  assert(c);

  field_set(field, 1000000, 0);
  c = field_index_update(index, field, 1000000);
  assert(c);
}
