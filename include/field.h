#ifndef FIELD_H
#define FIELD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#define FIELD_INDEX_LEN 2064

typedef uint8_t field_t[];
typedef uint8_t field_index_t[FIELD_INDEX_LEN];

bool
field_get (const field_t field, size_t bit);

bool
field_set (field_t field, size_t bit, bool value);

ssize_t
field_index_of (const field_t field, size_t field_len, bool value, size_t position, field_index_t index);

ssize_t
field_last_index_of (const field_t field, size_t field_len, bool value, size_t position, field_index_t index);

void
field_index_init (field_index_t index, const field_t field, size_t field_len, bool value);

#ifdef __cplusplus
}
#endif
#endif // FIELD_H
