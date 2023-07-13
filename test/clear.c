#include <assert.h>

#include "../include/quickbit.h"

#define field_len 32

int
main () {
  uint8_t field[field_len] = {0};

  quickbit_fill(field, field_len, true, 0, field_len * 8);

  uint8_t chunk[] = {
    0b11110000,
    0b00001111,
  };

  quickbit_clear(field, field_len, &(quickbit_chunk_t){.field = chunk, .len = 2, .offset = 2});

  for (size_t i = 0; i < field_len; i++) {
    switch (i) {
    case 2:
      assert(field[i] == 0b00001111);
      break;

    case 3:
      assert(field[i] == 0b11110000);
      break;

    default:
      assert(field[i] == 0b11111111);
    }
  }
}
