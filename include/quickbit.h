#ifndef QUICKBIT_H
#define QUICKBIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define QUICKBIT_INDEX_LEN 16 + 128 * 16

typedef uint8_t *quickbit_t;
typedef uint8_t quickbit_index_t[QUICKBIT_INDEX_LEN];

bool
quickbit_get (const quickbit_t field, size_t bit);

bool
quickbit_set (quickbit_t field, size_t bit, bool value);

size_t
quickbit_index_of (const quickbit_t field, size_t field_len, bool value, size_t position, quickbit_index_t index);

size_t
quickbit_last_index_of (const quickbit_t field, size_t field_len, bool value, size_t position, quickbit_index_t index);

void
quickbit_index_init (quickbit_index_t index, const quickbit_t field, size_t field_len);

bool
quickbit_index_update (quickbit_index_t index, const quickbit_t field, size_t bit);

#ifdef __cplusplus
}
#endif
#endif // QUICKBIT_H
