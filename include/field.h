#ifndef FIELD_H
#define FIELD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define FIELD_INDEX_LEN 2064

typedef uint8_t field_t[];

typedef struct field_index_s field_index_t;

struct field_index_s {
  uint8_t index[FIELD_INDEX_LEN];
  bool set;
};

bool
field_get (const field_t field, size_t bit);

bool
field_set (field_t field, size_t bit, bool value);

void
field_index_init (field_index_t *index, bool set, const field_t field, size_t field_len);

#ifdef __cplusplus
}
#endif
#endif // FIELD_H
