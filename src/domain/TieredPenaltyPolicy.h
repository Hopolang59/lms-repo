#pragma once
#include "domain/IPenaltyPolicy.h"

namespace lms::domain {

// BR-03: day 1 = 10%, day 2 = 20%, day 3 = 30%, day 4 or later = zero mark.
class TieredPenaltyPolicy : public IPenaltyPolicy {
public:
    // Throws ValidationError when daysLate is negative.
    double penaltyPercent(int daysLate) const override;
};

}  // namespace lms::domain
