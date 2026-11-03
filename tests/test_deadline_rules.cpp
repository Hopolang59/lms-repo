#include <gtest/gtest.h>

#include <chrono>

#include "domain/DeadlineRules.h"

using namespace std::chrono;
using lms::domain::daysLate;
using lms::domain::TimePoint;

namespace {
const TimePoint kDeadline = system_clock::time_point{} + hours(24 * 365 * 40);
}

// Boundary values from the SRS table for BR-02.
TEST(DeadlineRules, OnTimeAtOrBeforeDeadline) {
    EXPECT_EQ(daysLate(kDeadline, kDeadline), 0);
    EXPECT_EQ(daysLate(kDeadline, kDeadline - hours(5)), 0);
}

TEST(DeadlineRules, OneSecondLateIsDayOne) {
    EXPECT_EQ(daysLate(kDeadline, kDeadline + seconds(1)), 1);
}

TEST(DeadlineRules, PartOfASecondRoundsUp) {
    EXPECT_EQ(daysLate(kDeadline, kDeadline + milliseconds(1)), 1);
}

TEST(DeadlineRules, Exactly24HoursIsDayOne) {
    EXPECT_EQ(daysLate(kDeadline, kDeadline + hours(24)), 1);
}

TEST(DeadlineRules, 24HoursOneSecondIsDayTwo) {
    EXPECT_EQ(daysLate(kDeadline, kDeadline + hours(24) + seconds(1)), 2);
}

TEST(DeadlineRules, Exactly72HoursIsDayThree) {
    EXPECT_EQ(daysLate(kDeadline, kDeadline + hours(72)), 3);
}

TEST(DeadlineRules, 72HoursOneSecondIsDayFour) {
    EXPECT_EQ(daysLate(kDeadline, kDeadline + hours(72) + seconds(1)), 4);
}
