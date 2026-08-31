#!/usr/bin/env bash
# Quick build script, targets:
# - dragonfly_core
# - dragonflyc
# - dragonfly_tests
#
# Also you need to run setup.sh if you've added any soure files - HRS
set -euo pipefail
 
BUILD_DIR="build"
 
if [ ! -d "$BUILD_DIR" ]; then
    echo "No ${BUILD_DIR}/ directory found! Running setup.sh first..."
    ./setup.sh
fi
 
if [ "$#" -gt 0 ]; then
    echo "==> Building target(s): $*"
    cmake --build "$BUILD_DIR" --target "$@"
else
    echo "==> Building all targets..."
    cmake --build "$BUILD_DIR"
fi