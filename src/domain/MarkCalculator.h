#pragma once
#include "domain/IPenaltyPolicy.h"

namespace lms::domain {

// Final mark = awarded mark - penalty, never below zero (BR-03).
// Throws ValidationError when the awarded mark is outside 0..maxMark or maxMark <= 0.
double finalMark(double awardedMark, double maxMark, int daysLate, const IPenaltyPolicy& policy);

}  // namespace lms::domain
