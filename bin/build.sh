#!/bin/bash
set -x

cmake -B ./build

cmake --build ./build
