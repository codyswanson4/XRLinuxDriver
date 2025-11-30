#!/bin/bash

set -e

if [ -d build ]; then sudo rm -rf build/; fi
podman run --rm -t --mount="type=bind,source=./,destination=/source" --platform linux/amd64 "xr-driver:amd64"

# build directory structure is all owned by root because of docker, delete it all now
sudo rm -rf build/
