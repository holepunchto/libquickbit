cmake_minimum_required(VERSION 3.22)

project(field C)

add_subdirectory(vendor/libsimd EXCLUDE_FROM_ALL)

add_library(field OBJECT)

set_target_properties(
  field
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE 1
)

target_sources(
  field
  INTERFACE
    include/field.h
  PRIVATE
    src/field.c
)

target_include_directories(
  field
  PUBLIC
    include
  PRIVATE
    $<TARGET_PROPERTY:simd,INCLUDE_DIRECTORIES>
)

add_library(field_shared SHARED $<TARGET_OBJECTS:field>)

set_target_properties(
  field_shared
  PROPERTIES
  OUTPUT_NAME field
)

target_link_libraries(
  field_shared
  PUBLIC
    simd_shared
)

add_library(field_static STATIC $<TARGET_OBJECTS:field>)

set_target_properties(
  field_static
  PROPERTIES
  OUTPUT_NAME field
)

target_link_libraries(
  field_static
  PUBLIC
    simd_static
)

install(TARGETS field_shared field_static)

install(FILES include/field.h DESTINATION include)

enable_testing()

add_subdirectory(test)
