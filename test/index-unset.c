#include <assert.h>
#include <stdlib.h>

#include "../include/field.h"

int
main () {
  uint8_t *field = calloc(1 << 18, sizeof(uint8_t));

  field_index_t index;
  field_index_init(&index, 0, field, 1 << 18);

  return 0;
}
