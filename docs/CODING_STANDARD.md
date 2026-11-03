# Coding standard

This project follows the C++ Core Guidelines (https://isocpp.github.io/CppCoreGuidelines) with the project rules below. `.clang-format` formats the code and `.clang-tidy` and cppcheck check it.

## Naming

| Item | Style | Example |
|---|---|---|
| Classes, structs, enums | PascalCase | `TieredPenaltyPolicy`, `Role` |
| Interfaces | PascalCase with prefix `I` | `IPenaltyPolicy` |
| Functions and methods | camelCase | `penaltyPercent`, `findByUsername` |
| Private data members | camelCase with trailing underscore | `username_` |
| Local variables and parameters | camelCase | `maxMark` |
| Constants | `k` prefix and PascalCase | `kDeadline` |
| Namespaces | lowercase | `lms::domain` |
| Files | One class per file, named after the class | `UserFactory.h`, `UserFactory.cpp` |

## Layout

- 4 spaces, no tabs. Lines of at most 100 characters. Braces on every `if`, `for` and `while`.
- Headers start with `#pragma once`. Include project headers with the path from `src/`, for example `#include "domain/Role.h"`.
- Includes in this order: own header, standard library, project headers.

## Language rules

- C++17 only. No compiler extensions.
- No raw `new` or `delete`. Use `std::unique_ptr` and `std::make_unique`.
- Use RAII for anything that must be closed, including SQLite statements and transactions.
- Mark everything that does not change `const`. Pass large objects by `const&`.
- Use `enum class`, not plain enums. Use `override` on every overriding function.
- Never use `using namespace` in a header.

## Architecture rules (from the design document)

1. Layers call only the layer directly beneath them: UI, then application, then domain and data access.
2. SQL appears only in `src/data`, and only as prepared statements with bound parameters (NFR-10).
3. Passwords are never stored or logged in plain text (NFR-02).
4. Classes depend on interfaces such as `IUserRepository`, not on SQLite classes. Concrete objects are created in `main()`.

## Errors and validation

- Throw a class derived from `lms::LmsException` for invalid input, refused actions, missing records and database failures.
- Only the console UI catches `LmsException`. It shows `what()` and returns to a menu.
- Validate input at the boundary (UI and services) before it reaches the domain.

## Functions and comments

- A function does one job and is normally no longer than 40 lines.
- Public functions have a short comment that states what they do, what they return and what they throw. Comments explain why, not what.

## Tests

- Every business rule has unit tests, including boundary values.
- Tests are named `TEST(ClassName, WhatItChecks)`.
- Business-logic line coverage must stay at or above 70%.
