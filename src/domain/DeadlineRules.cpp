#include "domain/DeadlineRules.h"

namespace lms::domain {

int daysLate(TimePoint effectiveDeadline, TimePoint submittedAt) {
    if (submittedAt <= effectiveDeadline) {
        return 0;
    }
    const auto late = submittedAt - effectiveDeadline;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(late);
    if (seconds < late) {
        seconds += std::chrono::seconds(1);  // round any part of a second up
    }
    constexpr long long secondsPerDay = 24LL * 60 * 60;
    return static_cast<int>((seconds.count() + secondsPerDay - 1) / secondsPerDay);
}

}  // namespace lms::domain
