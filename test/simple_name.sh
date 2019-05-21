#!/bin/bash

set -e

PATH=$(dirname $(dirname $(readlink -f $0)))/build:$PATH
SRC_DIR=$(dirname $(readlink -f $0))/src

diff <(csv -f 2 $SRC_DIR/simple.csv) <(cat $SRC_DIR/simple_name.csv)

