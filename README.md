# libquickbit

The fastest bit in the West; a library for working with bit fields, accelerated using SIMD on supported hardware.

## API

See [`includes/quickbit.h`](include/quickbit.h) for the public API.

### Indexing

Several bit field operations take an optional index which, if provided, will substantially improve performance of these operations. An index is a 128-ary balanced tree of bits with a set bit in a branch indicating that all bits below are the same. An index has a fixed depth of 3 with leaves of the tree being the bit field itself. A single index can therefore contain 128^3 bits (256 KiB). To index more than 256 KiB, several indices may be used.

An index is initialised using `quickbit_index_init()` and maintained using `quickbit_index_update()`:

```c
quickbit_t field = malloc(256 * 1024);

quickbit_index_t index;
quickbit_index_init(index, field, 256 * 1024);

if (quickbit_set(field, 1000000, true)) {
  quickbit_index_update(index, field, 1000000);
}
```

## License

ISC
