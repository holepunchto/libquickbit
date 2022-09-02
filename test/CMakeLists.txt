list(APPEND tests
  get
  index-of
  index-of-indexed
  index-update
  set
)

foreach(test IN LISTS tests)
  add_executable(test_${test} ${test}.c)

  target_link_libraries(test_${test} field_static)

  add_test(
    NAME ${test}
    COMMAND test_${test}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
endforeach()
