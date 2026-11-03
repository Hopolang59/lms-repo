#include "domain/MarkCalculator.h"

#include <algorithm>

#include "common/Exceptions.h"

namespace lms::domain {

double finalMark(double awardedMark, double maxMark, int daysLate, const IPenaltyPolicy& policy) {
    if (maxMark <= 0.0) {
        throw ValidationError("Maximum mark must be greater than zero");
    }
    if (awardedMark < 0.0 || awardedMark > maxMark) {
        throw ValidationError("Mark must be between 0 and the maximum mark");
    }
    const double penalty = maxMark * policy.penaltyPercent(daysLate) / 100.0;
    return std::max(0.0, awardedMark - penalty);
}

}  // namespace lms::domain
