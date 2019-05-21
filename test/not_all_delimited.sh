#!/bin/bash

set -e

PATH=$(dirname $(dirname $(readlink -f $0)))/build:$PATH
SRC_DIR=$(dirname $(readlink -f $0))/src

diff <(csv $SRC_DIR/not_all_delimited.csv) <(cat $SRC_DIR/not_all_delimited.csv)

