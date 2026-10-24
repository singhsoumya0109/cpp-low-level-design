#!/usr/bin/env python3
"""
Lint and verify the repository structure against the agreed specification.
"""
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

REQUIRED_ROOT_FILES = [
    "README.md",
    "START-HERE.md",
    "ROADMAP.md",
    "STUDY-TRACKER.md",
    "LICENSE",
    "CMakeLists.txt",
    "CMakePresets.json",
    ".clang-format",
    ".gitignore",
]

REQUIRED_SECTIONS = [
    "00-Foundations",
    "01-Creational-Patterns",
    "02-Structural-Patterns",
    "03-Behavioral-Patterns",
    "04-Modern-Cpp-And-Extended-Patterns",
    "05-Pattern-Comparisons",
    "06-Pattern-Selection-Guide",
    "07-LLD-Case-Studies",
    "08-Interview-Preparation",
    "09-Revision-Center",
    "10-Reference",
]

def main():
    errors = []
    print(f"Checking repository structure in: {ROOT}")

    for rf in REQUIRED_ROOT_FILES:
        path = os.path.join(ROOT, rf)
        if not os.path.isfile(path):
            errors.append(f"Missing root file: {rf}")

    for sec in REQUIRED_SECTIONS:
        path = os.path.join(ROOT, sec)
        if not os.path.isdir(path):
            errors.append(f"Missing section directory: {sec}")

    if errors:
        print("\nStructure Validation Failed with errors:")
        for err in errors:
            print(f" - {err}")
        sys.exit(1)
    else:
        print("\nAll required root files and section directories exist!")
        sys.exit(0)

if __name__ == "__main__":
    main()

