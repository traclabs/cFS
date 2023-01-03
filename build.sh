#!/bin/bash
# pushd ../../..
make simulation=native prep && make && make install
# popd