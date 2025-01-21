#include <assert.h>

#include "../include/quickbit.h"

int
main() {
  uint8_t a[32] = {0};
  a[0] = 1;

  uint8_t b[32] = {0};
  b[0] = 1;

  quickbit_chunk_t chunks[2] = {
    {
      .field = a,
      .len = 32,
      .offset = 0,
    },
    {
      .field = b,
      .len = 32,
      .offset = 2048,
    },
  };

  quickbit_index_t index;
  quickbit_index_init_sparse(index, chunks, 2);

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
