cmake_minimum_required(VERSION 3.22)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

project(quickbit C)

add_subdirectory(vendor/libsimdle EXCLUDE_FROM_ALL)

add_library(quickbit OBJECT)

set_target_properties(
  quickbit
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE 1
)

target_sources(
  quickbit
  INTERFACE
    include/quickbit.h
  PRIVATE
    src/quickbit.c
)

target_include_directories(
  quickbit
  PUBLIC
    include
  PRIVATE
    $<TARGET_PROPERTY:simdle,INCLUDE_DIRECTORIES>
)

add_library(quickbit_shared SHARED $<TARGET_OBJECTS:quickbit>)

set_target_properties(
  quickbit_shared
  PROPERTIES
  OUTPUT_NAME quickbit
)

target_link_libraries(
  quickbit_shared
  PUBLIC
    simdle_shared
)

add_library(quickbit_static STATIC $<TARGET_OBJECTS:quickbit>)

set_target_properties(
  quickbit_static
  PROPERTIES
  OUTPUT_NAME quickbit
)

target_link_libraries(
  quickbit_static
  PUBLIC
    simdle_static
)

install(TARGETS quickbit_shared quickbit_static)

install(FILES include/quickbit.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(test)
endif()
