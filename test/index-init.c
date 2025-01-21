#include <assert.h>

#include "../include/quickbit.h"

#define field_len (1 << 18)

int
main() {
  uint8_t field[field_len] = {0};
  field[0] = 1;
  field[2048] = 1;

  quickbit_index_t index;
  quickbit_index_init(index, field, field_len);

  for (size_t i = 0; i < QUICKBIT_INDEX_LEN / 2; i++) {
    uint8_t v = index[i];

    switch (i) {
    case 0:
      assert(v == 0xfc);
      break;
    case 16:
    case 32:
      assert(v == 0xfe);
      break;
    default:
      assert(v == 0xff);
    }
  }
}
