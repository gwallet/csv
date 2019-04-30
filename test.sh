#!/bin/sh

ROOT_DIR=$(dirname $(readlink -f $0))
BUILD_DIR=$ROOT_DIR/build
TESTS_DIR=$ROOT_DIR/test.d
TEST_SRC_DIR=$TESTS_DIR/src

set -e
./build.sh
set +e

export PATH=$BUILD_DIR:$PATH

cd $ROOT_DIR
TESTS_FAILED=()
for TEST in $(ls -p1 $TESTS_DIR | grep -v /); do
  /bin/bash $TESTS_DIR/$TEST
  TEST_RESULT=$?
  if [ $TEST_RESULT != 0 ]; then
    echo -e "[\e[31m✘\e[0m] $TEST test failed"
    TESTS_FAILED+=($TEST)
  else
    echo -e "[\e[32m✔\e[0m] $TEST test passed"
  fi
done

if [ ${#TESTS_FAILED[@]} -gt 0 ]; then
  echo "There was ${#TESTS_FAILED[@]} test failures: ${TESTS_FAILED[@]}"
  exit 1
else
  echo "All test passed!"
fi

