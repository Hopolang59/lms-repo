#include <gtest/gtest.h>

#include "common/Exceptions.h"
#include "domain/MarkCalculator.h"
#include "domain/TieredPenaltyPolicy.h"

using lms::domain::finalMark;
using lms::domain::TieredPenaltyPolicy;

// Worked example from the SRS: maximum mark 50, awarded mark 40.
TEST(MarkCalculator, MatchesSrsBoundaryTable) {
    TieredPenaltyPolicy policy;
    EXPECT_NEAR(finalMark(40, 50, 0, policy), 40.0, 1e-9);
    EXPECT_NEAR(finalMark(40, 50, 1, policy), 35.0, 1e-9);
    EXPECT_NEAR(finalMark(40, 50, 2, policy), 30.0, 1e-9);
    EXPECT_NEAR(finalMark(40, 50, 3, policy), 25.0, 1e-9);
    EXPECT_NEAR(finalMark(40, 50, 4, policy), 0.0, 1e-9);
}

TEST(MarkCalculator, NeverBelowZero) {
    TieredPenaltyPolicy policy;
    EXPECT_NEAR(finalMark(10, 50, 3, policy), 0.0, 1e-9);
}

TEST(MarkCalculator, RejectsInvalidMarks) {
    TieredPenaltyPolicy policy;
    EXPECT_THROW(finalMark(-1, 50, 0, policy), lms::ValidationError);
    EXPECT_THROW(finalMark(51, 50, 0, policy), lms::ValidationError);
    EXPECT_THROW(finalMark(10, 0, 0, policy), lms::ValidationError);
}
