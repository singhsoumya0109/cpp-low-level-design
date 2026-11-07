#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(dirname "$SCRIPT_DIR")"

echo "=== Building cpp-low-level-design ==="
cd "$ROOT_DIR"

if command -v cmake >/dev/null 2>&1; then
    echo "Using CMake build system..."
    BUILD_TYPE=${1:-Debug}
    BUILD_DIR="$ROOT_DIR/build"
    cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
    cmake --build "$BUILD_DIR" -j "$(getconf _NPROCESSORS_ONLN 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)"
else
    echo "CMake not found in PATH. Using direct C++17 compiler (clang++/g++)..."
    COMPILER="clang++"
    if ! command -v clang++ >/dev/null 2>&1; then
        COMPILER="g++"
    fi

    mkdir -p "$ROOT_DIR/bin"
    echo "Compiler: $($COMPILER --version | head -n 1)"

    # Compile all pattern source files and tests found in the repo
    while IFS= read -r file; do
        rel_path="${file#$ROOT_DIR/}"
        target_name="$(basename "$file" .cpp)"
        category="$(basename "$(dirname "$(dirname "$file")")")"
        pattern="$(basename "$(dirname "$file")")"
        out_bin="$ROOT_DIR/bin/${category}_${pattern}_${target_name}"

        echo "  Compiling: $rel_path"
        $COMPILER -std=c++17 -Wall -Wextra -pthread "$file" -o "$out_bin"
    done < <(find "$ROOT_DIR" \( -path "$ROOT_DIR/01-*" -o -path "$ROOT_DIR/02-*" -o -path "$ROOT_DIR/03-*" -o -path "$ROOT_DIR/04-*" -o -path "$ROOT_DIR/07-*" \) -name "*.cpp" ! -name "starter.cpp")

fi

echo "=== Build Complete successfully! ==="

