list(APPEND tests
  fill
  get
  index-of
  index-of-indexed
  index-update
  index-update-sweep
  last-index-of
  last-index-of-indexed
  set
)

foreach(test IN LISTS tests)
  add_executable(${test} ${test}.c)

  target_link_libraries(${test} quickbit_shared)

  add_test(
    NAME ${test}
    COMMAND ${test}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
endforeach()
