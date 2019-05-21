#!/bin/bash

set -e

PATH=$(dirname $(dirname $(readlink -f $0)))/build:$PATH
SRC_DIR=$(dirname $(readlink -f $0))/src

diff <(csv -s ';' -f 1 $SRC_DIR/simple.scsv) <(cat $SRC_DIR/simple_id.csv)

diff <(csv -s ';' -f 2 $SRC_DIR/simple.scsv) <(cat $SRC_DIR/simple_name.csv)
