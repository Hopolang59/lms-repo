#include "domain/TieredPenaltyPolicy.h"

#include "common/Exceptions.h"

namespace lms::domain {

double TieredPenaltyPolicy::penaltyPercent(int daysLate) const {
    if (daysLate < 0) {
        throw ValidationError("Days late must not be negative");
    }
    switch (daysLate) {
    case 0:
        return 0.0;
    case 1:
        return 10.0;
    case 2:
        return 20.0;
    case 3:
        return 30.0;
    default:
        return 100.0;
    }
}

}  // namespace lms::domain
