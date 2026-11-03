#pragma once
#include "domain/User.h"

namespace lms::domain {

class Administrator : public User {
public:
    using User::User;
    Role role() const override { return Role::Administrator; }
    bool canPerform(Action action) const override;
};

class Lecturer : public User {
public:
    using User::User;
    Role role() const override { return Role::Lecturer; }
    bool canPerform(Action action) const override;
};

class HeadOfDepartment : public User {
public:
    using User::User;
    Role role() const override { return Role::HeadOfDepartment; }
    bool canPerform(Action action) const override;
};

class Student : public User {
public:
    using User::User;
    Role role() const override { return Role::Student; }
    bool canPerform(Action action) const override;
};

}  // namespace lms::domain
