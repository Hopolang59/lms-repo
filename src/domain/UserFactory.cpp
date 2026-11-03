#include "domain/UserFactory.h"

#include "common/Exceptions.h"
#include "domain/UserRoles.h"

namespace lms::domain {

std::unique_ptr<User> UserFactory::create(Role role, const UserDetails& d) {
    if (d.username.empty()) {
        throw ValidationError("Username must not be empty");
    }
    switch (role) {
    case Role::Administrator:
        return std::make_unique<Administrator>(d.id, d.username, d.passwordHash, d.salt, d.active,
                                               d.departmentId);
    case Role::Lecturer:
        return std::make_unique<Lecturer>(d.id, d.username, d.passwordHash, d.salt, d.active,
                                          d.departmentId);
    case Role::HeadOfDepartment:
        return std::make_unique<HeadOfDepartment>(d.id, d.username, d.passwordHash, d.salt,
                                                  d.active, d.departmentId);
    case Role::Student:
        return std::make_unique<Student>(d.id, d.username, d.passwordHash, d.salt, d.active,
                                         d.departmentId);
    }
    throw ValidationError("Unknown role");
}

}  // namespace lms::domain
