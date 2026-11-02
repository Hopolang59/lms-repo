cmake_minimum_required(VERSION 3.16)
project(ModeratedLMS VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(LMS_BUILD_TESTS "Build the unit tests" ON)
option(LMS_COVERAGE "Add coverage instrumentation (GCC or Clang)" OFF)

if(NOT MSVC)
  add_compile_options(-Wall -Wextra -Wpedantic)
  if(LMS_COVERAGE)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
  endif()
endif()

# Core library: domain rules and (later) application services and data access.
add_library(lms_core STATIC
  src/domain/Role.cpp
  src/domain/User.cpp
  src/domain/UserRoles.cpp
  src/domain/UserFactory.cpp
  src/domain/DeadlineRules.cpp
  src/domain/TieredPenaltyPolicy.cpp
  src/domain/MarkCalculator.cpp
)
target_include_directories(lms_core PUBLIC src)

# SQLite is added when the data-access layer is implemented:
#   find_package(SQLite3 REQUIRED)
#   target_link_libraries(lms_core PUBLIC SQLite::SQLite3)

add_executable(lms src/main.cpp)
target_link_libraries(lms PRIVATE lms_core)

if(LMS_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
