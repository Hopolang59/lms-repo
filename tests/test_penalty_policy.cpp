#include <gtest/gtest.h>

#include "common/Exceptions.h"
#include "domain/TieredPenaltyPolicy.h"

using lms::domain::TieredPenaltyPolicy;

TEST(TieredPenaltyPolicy, NoPenaltyWhenOnTime) {
    EXPECT_NEAR(TieredPenaltyPolicy().penaltyPercent(0), 0.0, 1e-9);
}

TEST(TieredPenaltyPolicy, TenTwentyThirtyPercentForDaysOneToThree) {
    TieredPenaltyPolicy policy;
    EXPECT_NEAR(policy.penaltyPercent(1), 10.0, 1e-9);
    EXPECT_NEAR(policy.penaltyPercent(2), 20.0, 1e-9);
    EXPECT_NEAR(policy.penaltyPercent(3), 30.0, 1e-9);
}

TEST(TieredPenaltyPolicy, WholeMarkLostFromDayFour) {
    TieredPenaltyPolicy policy;
    EXPECT_NEAR(policy.penaltyPercent(4), 100.0, 1e-9);
    EXPECT_NEAR(policy.penaltyPercent(30), 100.0, 1e-9);
}

TEST(TieredPenaltyPolicy, NegativeDaysAreRejected) {
    EXPECT_THROW(TieredPenaltyPolicy().penaltyPercent(-1), lms::ValidationError);
}
