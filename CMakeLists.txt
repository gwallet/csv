cmake_minimum_required (VERSION 3.14)

project (CSV C)

set (CSV_VERSION_MAJOR 1)
set (CSV_VERSION_MINOR 0)

set (PROJECT_SOURCE_DIR src)

set (CMAKE_C_STANDARD 11)

add_executable (csv
  ${PROJECT_SOURCE_DIR}/csv.c
)