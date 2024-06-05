try_compile(
  supports_fuzzing
  SOURCE_FROM_CONTENT
    entry.c
      "
      #include <stddef.h>
      #include <stdint.h>

      int LLVMFuzzerTestOneInput (const uint8_t *data, size_t size) {}
      "
  LINK_OPTIONS -fsanitize=fuzzer
)

if(NOT supports_fuzzing)
  return()
endif()

list(APPEND fuzzers
  index-fill
)

foreach(fuzzer IN LISTS fuzzers)
  set(target fuzz_${fuzzer})

  add_executable(${target} ${fuzzer}.c)

  set_target_properties(
    ${target}
    PROPERTIES
    OUTPUT_NAME ${fuzzer}
  )

  target_link_libraries(
    ${target}
    PRIVATE
      quickbit_static
  )

  target_compile_options(
    ${target}
    PRIVATE
      -fsanitize=fuzzer
  )

  target_link_options(
    ${target}
    PRIVATE
      -fsanitize=fuzzer
  )
endforeach()
