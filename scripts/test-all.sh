#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(dirname "$SCRIPT_DIR")"

echo "=== Running all Unit & Concurrency Tests ==="
cd "$ROOT_DIR"

if command -v ctest >/dev/null 2>&1 && [ -d "$ROOT_DIR/build" ]; then
    echo "Running via CTest..."
    ctest --test-dir "$ROOT_DIR/build" --output-on-failure
else
    echo "Running standalone test binaries..."
    # Ensure build has run
    if [ ! -d "$ROOT_DIR/bin" ] || [ -z "$(ls -A "$ROOT_DIR/bin" 2>/dev/null)" ]; then
        "$SCRIPT_DIR/build-all.sh"
    fi

    TOTAL_TESTS=0
    PASSED_TESTS=0

    for test_bin in "$ROOT_DIR/bin"/*test*; do
        if [ -x "$test_bin" ]; then
            TOTAL_TESTS=$((TOTAL_TESTS + 1))
            test_name="$(basename "$test_bin")"
            echo "----------------------------------------"
            echo "Running: $test_name"
            if "$test_bin"; then
                PASSED_TESTS=$((PASSED_TESTS + 1))
            else
                echo "FAILED: $test_name"
                exit 1
            fi
        fi
    done

    echo "----------------------------------------"
    echo "=== Summary: $PASSED_TESTS / $TOTAL_TESTS test suites passed! ==="
fi

