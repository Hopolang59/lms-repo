#include <gtest/gtest.h>

#include "common/Exceptions.h"
#include "domain/UserFactory.h"

using namespace lms::domain;

namespace {
UserDetails details(const std::string& name) {
    UserDetails d;
    d.id = 1;
    d.username = name;
    d.passwordHash = "hash";
    d.salt = "salt";
    d.departmentId = 2;
    return d;
}
}  // namespace

TEST(UserFactory, BuildsTheRightSubclassForEachRole) {
    for (Role r : {Role::Administrator, Role::Lecturer, Role::HeadOfDepartment, Role::Student}) {
        auto user = UserFactory::create(r, details("u"));
        ASSERT_NE(user, nullptr);
        EXPECT_EQ(user->role(), r);
    }
}

TEST(UserFactory, RejectsEmptyUsername) {
    EXPECT_THROW(UserFactory::create(Role::Student, details("")), lms::ValidationError);
}

TEST(UserRoles, StudentCanSubmitButNotMark) {
    auto s = UserFactory::create(Role::Student, details("s"));
    EXPECT_TRUE(s->canPerform(Action::SubmitAssignment));
    EXPECT_FALSE(s->canPerform(Action::MarkSubmission));
}

TEST(UserRoles, OnlyHodCanModerateAndRelease) {
    auto hod = UserFactory::create(Role::HeadOfDepartment, details("h"));
    auto lec = UserFactory::create(Role::Lecturer, details("l"));
    EXPECT_TRUE(hod->canPerform(Action::ModerateMarks));
    EXPECT_TRUE(hod->canPerform(Action::ReleaseMarks));
    EXPECT_FALSE(lec->canPerform(Action::ReleaseMarks));
}

TEST(UserRoles, RoleTextMatchesDatabaseValues) {
    EXPECT_EQ(toString(Role::HeadOfDepartment), "HOD");
    EXPECT_EQ(roleFromString("STUDENT"), Role::Student);
    EXPECT_THROW(roleFromString("TEACHER"), lms::ValidationError);
}
