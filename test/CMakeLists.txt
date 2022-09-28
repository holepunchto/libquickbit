list(APPEND tests
  fill
  find-first
  find-first-indexed
  find-last
  find-last-indexed
  get
  index-init-sparse
  index-update
  index-update-sweep
  set
  skip-backward
  skip-forward
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
