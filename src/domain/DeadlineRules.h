#pragma once
#include <chrono>

namespace lms::domain {

using TimePoint = std::chrono::system_clock::time_point;

// BR-02: number of started 24-hour periods between the effective deadline and the
// submission time. Returns 0 when the work is on time (at or before the deadline).
int daysLate(TimePoint effectiveDeadline, TimePoint submittedAt);

}  // namespace lms::domain
