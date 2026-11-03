#pragma once
#include <memory>
#include <string>

#include "domain/Role.h"
#include "domain/User.h"

namespace lms::domain {

struct UserDetails {
    int id = 0;
    std::string username;
    std::string passwordHash;
    std::string salt;
    bool active = true;
    int departmentId = 0;
};

// Factory pattern: the only place that decides which User subclass to build.
class UserFactory {
public:
    // Throws ValidationError when the username is empty.
    static std::unique_ptr<User> create(Role role, const UserDetails& details);
};

}  // namespace lms::domain
