#!/bin/sh

cmake --build ./cmake-build-release --target checkers
./cmake-build-release/checkers
