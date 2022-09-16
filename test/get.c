#include <assert.h>

#include "../include/quickbit.h"

int
main () {
  const size_t field_len = 1 << 18;
  uint8_t field[field_len] = {0};

  field[100000] = 0xff;
  assert(quickbit_get(field, field_len, 800000) == 1);

  field[100000] = 0xfe;
  assert(quickbit_get(field, field_len, 800000) == 0);
}
