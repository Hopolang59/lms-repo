#include "domain/UserRoles.h"

#include <algorithm>
#include <initializer_list>

namespace lms::domain {

namespace {
bool contains(std::initializer_list<Action> allowed, Action action) {
    return std::find(allowed.begin(), allowed.end(), action) != allowed.end();
}
}  // namespace

bool Administrator::canPerform(Action action) const {
    return contains({Action::ManageUsers, Action::ManageDepartmentsAndCourses,
                     Action::AssignLecturers, Action::EnrolStudents, Action::ViewAuditLog},
                    action);
}

bool Lecturer::canPerform(Action action) const {
    return contains({Action::CreateAssignment, Action::GrantExtension, Action::MarkSubmission},
                    action);
}

bool HeadOfDepartment::canPerform(Action action) const {
    return contains({Action::ReviewDepartmentMarks, Action::ModerateMarks, Action::ReleaseMarks,
                     Action::ViewAuditLog},
                    action);
}

bool Student::canPerform(Action action) const {
    return contains({Action::ViewCourses, Action::SubmitAssignment, Action::ViewReleasedMarks},
                    action);
}

}  // namespace lms::domain
