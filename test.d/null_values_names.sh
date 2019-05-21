#!/bin/bash

set -e

PATH=$(dirname $(dirname $(readlink -f $0)))/build:$PATH
SRC_DIR=$(dirname $(readlink -f $0))/src

diff <(csv -f 2,3 $SRC_DIR/null_values.csv) <(cat $SRC_DIR/null_values_names.csv)

