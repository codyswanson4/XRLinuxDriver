#!/bin/bash

set -e

# Run containers for each architecture
if [[ "$1" == "x86_64" || -z "$1" ]]; then
    rm -rf build/
    podman run --rm -t -v ./:/source --platform linux/amd64 "xr-driver:amd64"
fi

if [[ "$1" == "aarch64" || -z "$1"  ]]; then
    rm -rf build/
    podman run --rm -t -v ./:/source --platform linux/arm64 "xr-driver:arm64"
fi

# build directory structure is all owned by root because of podman, delete it all now
rm -rf build/
