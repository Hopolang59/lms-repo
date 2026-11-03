#pragma once

namespace lms::domain {

// Things a user may try to do. Each role allows a fixed subset (see UserRoles.cpp).
enum class Action {
    ManageUsers,
    ManageDepartmentsAndCourses,
    AssignLecturers,
    EnrolStudents,
    CreateAssignment,
    GrantExtension,
    MarkSubmission,
    ViewCourses,
    SubmitAssignment,
    ViewReleasedMarks,
    ReviewDepartmentMarks,
    ModerateMarks,
    ReleaseMarks,
    ViewAuditLog
};

}  // namespace lms::domain
