# Moderated Learning Management System (LMS)

CS4433 Software Engineering, National University of Lesotho. Individual final project.

An offline C++17 application with SQLite storage for a secondary school. It manages courses, assignments, submissions and marks for four roles: administrator, lecturer, Head of Department (HoD) and student. Students see marks only after the HoD has moderated and released them, and every mark change is written to an audit log.

## Status

| Area | State |
|---|---|
| Project structure, CMake, CI, coding standard | Done |
| Domain: roles, `User` hierarchy, `UserFactory` | Done |
| Domain: deadline rules (BR-02), penalty policy (BR-03), final mark | Done, with unit tests |
| SQL schema (`db/schema.sql`) | Done |
| Data-access layer (SQLite repositories) | Interfaces only, implementation next |
| Password hashing, authentication | To do |
| Services (submit, mark, moderate, release, audit logger) | To do |
| Console user interface | To do |

## Folder layout

| Folder | Contents | Layer in the design |
|---|---|---|
| `src/common` | Exception classes | Shared |
| `src/domain` | Roles, users, penalty policy, mark calculation | Domain |
| `src/application` | Services (one per group of use cases) | Application |
| `src/data` | Repository interfaces and SQLite implementations | Data access |
| `src/ui` | Console menus | Presentation |
| `db` | SQL schema | Data access |
| `tests` | GoogleTest unit tests | Verification |
| `docs` | Coding standard, branching strategy | Configuration management |

## Build guide

Requirements: a C++17 compiler (GCC 9+, Clang 10+ or MSVC 2019+), CMake 3.16+, Git. SQLite development files are needed once the data-access layer is added (`libsqlite3-dev` on Ubuntu). GoogleTest is downloaded automatically by CMake when it is not installed, so the first configure needs an internet connection.

```
git clone <repository-url>
cd <repository-folder>
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/lms            # on Windows: build\Debug\lms.exe
```

Create an empty database from the schema (needs the `sqlite3` command-line tool):

```
sqlite3 lms.db < db/schema.sql
```

## Coverage (Linux or macOS with GCC or Clang)

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DLMS_COVERAGE=ON
cmake --build build --parallel
ctest --test-dir build
gcovr -r . --filter src/ --exclude src/main.cpp --print-summary
```

## Working with Git

See `docs/BRANCHING.md` for the branching strategy and commit messages, and `docs/CODING_STANDARD.md` for the coding standard.
