#pragma once

namespace lms::domain {

// Strategy pattern: how much of the maximum mark is lost for late work.
class IPenaltyPolicy {
public:
    virtual ~IPenaltyPolicy() = default;

    // Percentage of the assignment's maximum mark to deduct (0 to 100).
    // A value of 100 means the final mark is zero.
    virtual double penaltyPercent(int daysLate) const = 0;
};

}  // namespace lms::domain
