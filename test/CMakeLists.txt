list(APPEND tests
  clear
  fill
  find-first
  find-first-indexed
  find-last
  find-last-indexed
  get
  index-fill
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
  set(target test_${test})

  add_executable(${target} ${test}.c)

  set_target_properties(
    ${target}
    PROPERTIES
    OUTPUT_NAME ${test}
  )

  target_link_libraries(
    ${target}
    PRIVATE
      quickbit_static
  )

  add_test(
    NAME ${target}
    COMMAND ${target}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

  set_tests_properties(
    ${target}
    PROPERTIES
    TIMEOUT 30
  )
endforeach()

add_subdirectory(fuzz)
