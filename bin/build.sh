#!/bin/bash
# @author Simon de Hartog <simon@fs2a.pro>
# @copyright Fs2a Ltd. (c) 2018

repo="$(git rev-parse --show-toplevel)"

cd $repo/bld
test -f Makefile || cmake -DCMAKE_BUILD_TYPE=Debug ..
make "$@"
