#!/usr/bin/env bash
# Set this up in case I need to reconfigure cmake or need to set up the project again somewhere else

set -euo pipefail
 
BUILD_DIR="build"
 
echo "==> Checking prerequisites (Homebrew, CMake, LLVM, Ninja)..."
 
# I run on MacOS, so this uses brew
# If you're reading this and running on a different OS try to install the dependencies through your package manager or installers 
for pkg in cmake llvm ninja; do
    if ! brew list "$pkg" >/dev/null 2>&1; then
        echo "==> Installing $pkg via Homebrew..."
        brew install "$pkg"
    fi
done
 
LLVM_PREFIX="$(brew --prefix llvm)"
echo "==> Using LLVM at: $LLVM_PREFIX"
 
echo "==> Configuring CMake in ./${BUILD_DIR}..."
cmake -S . -B "$BUILD_DIR" -G Ninja -DCMAKE_PREFIX_PATH="$LLVM_PREFIX"
 
echo "==> Done!!"
 