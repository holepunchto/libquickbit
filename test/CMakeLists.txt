list(APPEND tests
  clear
  fill
  find-first
  find-first-indexed
  find-last
  find-last-indexed
  get
  index-fill
  index-fill-aligned
  index-init
  index-init-sparse
  index-update
  index-update-sweep
  set
  skip-first
  skip-last
  skip-last-index-boundary
)

foreach(test IN LISTS tests)
  add_executable(${test} ${test}.c)

  target_link_libraries(
    ${test}
    PRIVATE
      quickbit_static
  )

  add_test(
    NAME ${test}
    COMMAND ${test}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

  set_tests_properties(
    ${test}
    PROPERTIES
    TIMEOUT 30
  )
endforeach()

add_subdirectory(fuzz)
