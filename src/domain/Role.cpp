#include "domain/Role.h"

#include "common/Exceptions.h"

namespace lms::domain {

std::string toString(Role role) {
    switch (role) {
    case Role::Administrator:
        return "ADMIN";
    case Role::Lecturer:
        return "LECTURER";
    case Role::HeadOfDepartment:
        return "HOD";
    case Role::Student:
        return "STUDENT";
    }
    throw ValidationError("Unknown role");
}

Role roleFromString(const std::string& text) {
    if (text == "ADMIN") {
        return Role::Administrator;
    }
    if (text == "LECTURER") {
        return Role::Lecturer;
    }
    if (text == "HOD") {
        return Role::HeadOfDepartment;
    }
    if (text == "STUDENT") {
        return Role::Student;
    }
    throw ValidationError("Unknown role: " + text);
}

}  // namespace lms::domain
