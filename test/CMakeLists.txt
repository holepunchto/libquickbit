list(APPEND tests
  fill
  find-first
  find-first-indexed
  find-last
  find-last-indexed
  get
  index-init
  index-init-sparse
  index-update
  index-update-sweep
  set
  skip-first
  skip-last
)

foreach(test IN LISTS tests)
  add_executable(${test} ${test}.c $<TARGET_OBJECTS:quickbit>)

  add_test(
    NAME ${test}
    COMMAND ${test}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

  set_tests_properties(
    ${test}
    PROPERTIES
    TIMEOUT 30000
  )
endforeach()
