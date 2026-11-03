find_package(GTest QUIET)
if(GTest_FOUND)
  set(LMS_GTEST_TARGET GTest::gtest_main)
else()
  include(FetchContent)
  FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  set(LMS_GTEST_TARGET gtest_main)
endif()

add_executable(lms_tests
  test_deadline_rules.cpp
  test_penalty_policy.cpp
  test_mark_calculator.cpp
  test_user_factory.cpp
)
target_link_libraries(lms_tests PRIVATE lms_core ${LMS_GTEST_TARGET})

include(GoogleTest)
gtest_discover_tests(lms_tests)
