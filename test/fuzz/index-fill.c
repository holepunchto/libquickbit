#include <assert.h>
#include <quickbit.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int
LLVMFuzzerTestOneInput (const uint8_t *data, size_t size) {
  int e;

  if (size != 12) return -1;

  const uint32_t *bounds = (const uint32_t *) data;

  uint32_t start = bounds[0];
  uint32_t end = bounds[1];
  uint32_t field_len = bounds[2];

  if (
    start >= end ||
    end - start < 256 /* At least 2 leaves */ ||
    end > field_len * 8 ||
    field_len % 16 != 0 /* Must be 128-bit aligned */ ||
    field_len > 262144 /* 256 KiB */
  ) return -1;

  uint8_t *field = calloc(field_len, sizeof(uint8_t));

  quickbit_index_t index;
  quickbit_index_init(index, field, field_len);

  quickbit_fill(field, field_len, 1, start, end);

  e = quickbit_index_fill(index, field, field_len, 1, start, end);
  assert(e == 0);

  int64_t p;

  p = quickbit_skip_first(index, field_len, 0, 0);
  assert(p <= start);

  p = quickbit_skip_first(index, field_len, 1, start + 128);
  assert(p >= start && p <= end);

  free(field);

  return 0;
}
