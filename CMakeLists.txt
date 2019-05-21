cmake_minimum_required (VERSION 3.9)

project (
  CSV
  VERSION 1.1.0
  DESCRIPTION "Comma Separated Value file manipulation utility."
  LANGUAGES C
)

set (CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/gwallet/csv")
set (CMAKE_C_STANDARD 11)

add_executable (csv
  src/csv.c
)

enable_testing()

file(GLOB TEST_CASES test/*.sh LIST_DIRECTORIES false)
foreach(TEST_CASE ${TEST_CASES})
  string(REPLACE "${CMAKE_SOURCE_DIR}/test/" "" TEST_NAME ${TEST_CASE})
  string(REPLACE ".sh" "" TEST_NAME ${TEST_NAME})
  add_test(
    NAME ${TEST_NAME}
    COMMAND ${TEST_CASE}
  )
endforeach()

# add_test(NAME acceptance
#   WORKING_DIRECTORY ../
#   COMMAND test.sh
# )

install(
  FILES doc/csv.1
  DESTINATION "${CMAKE_INSTALL_PREFIX}/man/man1"
)

install(
  TARGETS csv
  RUNTIME DESTINATION bin
)
