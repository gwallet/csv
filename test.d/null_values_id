#!/bin/bash

set -e

SRC_DIR=$(dirname $(readlink -f $0))/src

diff <(csv -f 1 $SRC_DIR/null_values.csv) <(cat $SRC_DIR/null_values_id.csv)

