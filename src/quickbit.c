#include <simdle.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../include/quickbit.h"

static inline bool
quickbit_get_unchecked (const quickbit_t field, uint64_t bit) {
  uint64_t offset = bit & 7;
  uint64_t i = bit / 8;

  return (field[i] & (1 << offset)) != 0;
}

bool
quickbit_get (const quickbit_t field, size_t field_len, int64_t bit) {
  if (bit < 0) bit += field_len * 8;

  return quickbit_get_unchecked(field, (uint64_t) bit);
}

static inline bool
quickbit_set_unchecked (quickbit_t field, uint64_t bit, bool value) {
  uint64_t offset = bit & 7;
  uint64_t i = bit / 8;
  uint64_t mask = 1 << offset;

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

bool
quickbit_set (quickbit_t field, size_t field_len, int64_t bit, bool value) {
  if (bit < 0) bit += field_len * 8;

  return quickbit_set_unchecked(field, (uint64_t) bit, value);
}

void
quickbit_fill (const quickbit_t field, size_t field_len, bool value, int64_t start, int64_t end) {
  if (start < 0) start += field_len * 8;
  if (end < 0) end += field_len * 8;

  int64_t n = end - start;
  if (n < 0) return;

  int64_t i = start / 8;
  int64_t j = end / 8;

  {
    int64_t offset = start & 7;

    if (offset != 0) {
      uint8_t shift = 8 - offset;
      if (n < shift) shift = n;

      uint8_t mask = ((1 << shift) - 1) << offset;

      if (value) field[i] |= mask;
      else field[i] &= ~mask;

      i++;
    }
  }

  {
    int64_t offset = end & 7;

    if (offset != 0 && j >= i) {
      uint8_t mask = (1 << offset) - 1;

      if (value) field[j] |= mask;
      else field[j] &= ~mask;
    }
  }

  if (i < j) memset(&field[i], value ? 0xff : 0, j - i);
}

int64_t
quickbit_index_of (const quickbit_t field, size_t field_len, bool value, int64_t position, quickbit_index_t index) {
  int64_t n = field_len * 8;
  if (n == 0) return (int64_t) -1;

  if (position < 0) position += n;

  if (index != NULL) {
    int64_t i = position / 16384;

    while (i < 128 && quickbit_get_unchecked(index, i)) {
      int64_t bit = i * 16384;

      if (bit >= n || quickbit_get_unchecked(field, bit) == value) break;

      i++;
    }

    int64_t k = i * 16384;
    int64_t j = 0;

    if (position > k) j = (position - k) / 128;

    while (j < 128 && quickbit_get_unchecked(index, i * 128 + j + 128)) {
      int64_t bit = k + j * 128;

      if (bit >= n || quickbit_get_unchecked(field, bit) == value) break;

      j++;
    }

    int64_t l = k + j * 128;

    if (l > position) position = l;
  }

  int64_t i = position;

  while (i < n && quickbit_get_unchecked(field, i) != value) {
    i++;
  }

  return i < n ? i : (int64_t) -1;
}

int64_t
quickbit_last_index_of (const quickbit_t field, size_t field_len, bool value, int64_t position, quickbit_index_t index) {
  int64_t n = field_len * 8;
  if (n == 0) return (int64_t) -1;

  if (position < 0) position += n;

  if (index != NULL) {
    int64_t i = position / 16384;

    while (i >= 0 && quickbit_get_unchecked(index, i)) {
      int64_t bit = i * 16384;

      if (i == 0 || bit >= n || quickbit_get_unchecked(field, bit) == value) break;

      i--;
    }

    int64_t k = ((i + 1) * 16384) - 1;
    int64_t j = 127;

    if (position < k) j = (k - position) / 128;

    while (j >= 0 && quickbit_get_unchecked(index, i * 128 + j + 128)) {
      int64_t bit = k + j * 128;

      if (j == 0 || bit >= n || quickbit_get_unchecked(field, bit) == value) break;

      j--;
    }

    int64_t l = k + ((j + 1) * 128) - 1;

    if (l < position) position = l;
  }

  int64_t i = position;

  while (i >= 0 && quickbit_get_unchecked(field, i) != value) {
    i--;
  }

  return i < n ? i : (int64_t) -1;
}

void
quickbit_index_init (quickbit_index_t index, const quickbit_t field, size_t field_len) {
  for (int64_t i = 0; i < 128; i++) {
    bool all_z = true;
    bool all_o = true;

    for (int64_t j = 0; j < 128; j++) {
      int64_t offset = (i * 128 + j) * 16;
      int16_t sum = -1;

      if (offset + 16 <= (int64_t) field_len) {
        sum = simdle_sum_v128_u8(simdle_load_v128_u8(&field[offset]));
      }

      quickbit_set_unchecked(index, i * 128 + 128 + j, sum == 0 || sum == 0xff * 16);

      all_z = all_z && sum == 0;
      all_o = all_o && sum == 0xff * 16;
    }

    quickbit_set_unchecked(index, i, all_z || all_o);
  }
}

bool
quickbit_index_update (quickbit_index_t index, const quickbit_t field, size_t field_len, int64_t bit) {
  if (bit < 0) bit += field_len * 8;

  int64_t j = bit / 128;

  uint16_t sum = simdle_sum_v128_u8(simdle_load_v128_u8(&field[j * 16]));

  if (quickbit_set_unchecked(index, 128 + j, sum == 0 || sum == 0xff * 16)) {
    int64_t i = bit / 16384;

    sum = simdle_sum_v128_u8(simdle_load_v128_u8(&index[i * 16 + 16]));

    if (sum == 0xff * 16) {
      bool all_z = true;
      bool all_o = true;

      for (int64_t j = 0; j < 128; j++) {
        int64_t offset = (i * 128 + j) * 16;
        int64_t sum = -1;

        if (offset + 16 <= (int64_t) field_len) {
          sum = field[offset];
        }

        all_z = all_z && sum == 0;
        all_o = all_o && sum == 0xff;

        if (!all_z && !all_o) break;
      }

      quickbit_set_unchecked(index, i, all_z || all_o);
    } else {
      quickbit_set_unchecked(index, i, 0);
    }

    return true;
  }

  return false;
}
