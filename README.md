# mllhep

**Project**: `mllhep`, a machine learning library written in C (Raw C11).

**About**: Experimental particle physics produces large volumes of reconstructed collision events that must be separated into signal and background before any measurement can be made. `mllhep` is a C library that provides the classical and deep learning building blocks for that classification task. At this commit the repository contains the numeric type aliases, the build system and the unit test harness that the rest of the library is built on.

---

## Table of Contents
1. General Description
2. Software Testing

---

## General Description

### Overview

`mllhep` is organised as a static C library with an accompanying test suite. The build is driven by `Makefile`, which archives the library sources under `src/` into `build/libmllhep.a` and compiles each test under `tests/` into its own executable.

Layered architecture (current):
```
types.h  --->  src/  --->  tests/
```

| Layer | Folder | Responsibility |
|-------|--------|----------------|
| Numeric types | `types.h` | Fixed-width integer and floating point aliases used throughout the library. |
| Library | `src/` | Machine learning implementation. Not yet populated at this commit. |
| Tests | `tests/` | Unit tests and the `test.h` assertion harness. |

**Main components**
- **`types.h`** - defines the numeric aliases (`i8` to `i64`, `u8` to `u64`, `f32`, `f64`, `usize`, `isize`). Wraps `<stdint.h>` and `<stddef.h>` so the rest of the library never spells out a raw C integer type.
- **`tests/test.h`** - single-header assertion harness. Each test file is an independent executable that reports a pass or fail summary through `test_summary()`.
- **`tests/test_types.c`** - checks that every alias in `types.h` has the width and signedness the library assumes.

### Installation Instructions

**Prerequisites**

| Requirement | Notes |
|-------------|-------|
| C11 compiler | `cc`, `gcc` or `clang`. |
| `make` | Drives the build. |

**Step-by-step setup**
```bash
git clone https://github.com/Joekrry/mllhep
cd mllhep
make
```
`make` archives the static library into `build/`. The `build/` directory is created on demand and is not tracked in version control.

### Usage Instructions

Build the library and run the full test suite:
```bash
make test
```

| Path | Contents |
|------|----------|
| `build/libmllhep.a` | Compiled static library. |
| `build/test_*` | Compiled test executables. |

---

## Software Testing

### Testing Framework

**Framework Used**: a small in-repository harness, `tests/test.h` (no external test framework).

**Testing Approach**: each test source compiles to a standalone executable that exercises one area of the library and returns a non-zero exit code on failure. `make test` builds and runs every `tests/test_*.c`, so a failing check breaks the build. The tests are hermetic and take no external input.

### Test Cases

| Fixture | Tests | Purpose |
|---------|-------|---------|
| `tests/test_types.c` | 12 | Confirms the width and signedness of every alias in `types.h`. |
| **Total** | **12** | |

### Test Results
```bash
make test
```
Expected output ends with `PASS types (12 checks)` and an overall zero exit status. To run a single fixture, build and invoke it directly, for example `make build/test_types && ./build/test_types`.
