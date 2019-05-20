cmake_minimum_required (VERSION 3.14)

project (
  CSV
  VERSION 1.0.0
  DESCRIPTION "Comma Separated Value file manipulation utility."
  HOMEPAGE_URL "https://github.com/gwallet/csv"
  LANGUAGES C
)

set (CMAKE_C_STANDARD 11)

add_executable (csv
  src/csv.c
)

enable_testing()

add_test(NAME acceptance
  WORKING_DIRECTORY ../
  COMMAND test.sh
)

install(
  FILES doc/csv.1
  DESTINATION "${CMAKE_INSTALL_PREFIX}/man/man1"
)

install(
  TARGETS csv
  RUNTIME
)
