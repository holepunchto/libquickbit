#include <assert.h>

#include "../include/quickbit.h"

int
main () {
  uint8_t a[48] = {0};
  uint8_t b[32] = {0};

  quickbit_chunk_t chunks[2] = {
    {
      .field = a,
      .len = 48,
      .offset = 0,
    },
    {
      .field = b,
      .len = 32,
      .offset = 1024,
    },
  };

  quickbit_index_t index;
  quickbit_index_init_sparse(index, chunks, 2);
}
