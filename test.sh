#!/usr/bin/env bash
# builds and runs the GoogleTest suite
# thought it would be easier to set up a SPECIFICATION.md and tests before diving into building
#
# Commandss:
#   ./test.sh                                  # run everything (A LOT OF DETAIL)
#   ./test.sh --ctest                          # run just a summary, and only detail on failures
#
# Any arguments are forwarded straight to the dragonfly_tests binary except --ctest which switches runner.

set -euo pipefail

BUILD_DIR="build"
TEST_BINARY="${BUILD_DIR}/tests/dragonfly_tests"

if [ ! -d "$BUILD_DIR" ]; then
    echo "No ${BUILD_DIR}/ directory found! Running setup.sh first..."
    ./setup.sh
fi

echo "==> Building dragonfly_tests..."
cmake --build "$BUILD_DIR" --target dragonfly_tests

if [ "${1:-}" = "--ctest" ]; then
    shift
    echo "==> Running via ctest..."
    ctest --test-dir "$BUILD_DIR" --output-on-failure "$@"
else
    echo "==> Running dragonfly_tests..."
    "./${TEST_BINARY}" "$@"
fi