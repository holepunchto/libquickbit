#include <simd.h>
#include <stddef.h>
#include <stdint.h>

#include "../include/field.h"

bool
field_get (const field_t field, size_t bit) {
  size_t offset = bit & 7;
  size_t i = (bit - offset) / 8;

  return (field[i] & (1 << offset)) != 0;
}

bool
field_set (field_t field, size_t bit, bool value) {
  size_t offset = bit & 7;
  size_t i = (bit - offset) / 8;
  size_t mask = 1 << offset;

  if (value) {
    if ((field[i] & mask) != 0) {
      return false;
    }
  } else {
    if ((field[i] & mask) == 0) {
      return false;
    }
  }

  field[i] ^= mask;

  return true;
}

void
field_index_init (field_index_t *index, bool set, const field_t field, size_t field_len) {
  index->set = set;

  for (size_t i = 0; i < 128; i++) {
    uint64_t total = 0;

    for (size_t j = 0; j < 128; j++) {
      simd_v128_t v = simd_load_v128_u8(&field[(i * 128 + j) * 16]);

      uint64_t c = simd_sum_v128_u8(simd_cnt_v128_u8(v));

      field_set(index->index, i * 128 + j + 128, c == (set ? 128 : 0));

      c += total;
    }

    field_set(index->index, i, total == (set ? 16384 : 0));
  }
}
