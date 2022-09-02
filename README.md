# libfield

A library for working with bit fields, accelerated using SIMD on supported hardware.

## API

See [`includes/field.h`](include/field.h) for the public API.

### Indexing

Several bit field operations take an optional index which, if provided, will substantially improve performance of these operations. An index is a 128-ary balanced tree of bits with a set bit in a branch indicating that all bits below are the same. An index has a fixed depth of 3 with leaves of the tree being the bit field itself. A single index can therefore contain 128^3 bits (256 KiB). To index more than 256 KiB, several indices may be used.

An index is initialised using `field_index_init()` and maintained using `field_index_update()`:

```c
field_t field = malloc(256 * 1024);

field_index_t index;
field_index_init(index, field, 256 * 1024);

if (field_set(field, 1000000, true)) {
  field_index_update(index, field, 1000000);
}
```

## License

ISC
