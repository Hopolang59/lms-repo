#pragma once
#include <string>

namespace lms::domain {

enum class Role { Administrator, Lecturer, HeadOfDepartment, Student };

// Text stored in the database: ADMIN, LECTURER, HOD, STUDENT.
std::string toString(Role role);

// Throws ValidationError for unknown text.
Role roleFromString(const std::string& text);

}  // namespace lms::domain
