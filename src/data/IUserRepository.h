#pragma once
#include <memory>
#include <string>

#include "domain/User.h"

namespace lms::data {

// Repository pattern: the only way the rest of the program reads or writes users.
// The SQLite implementation (SqliteUserRepository) is added in the data-access step.
class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    // Returns nullptr when no user has that username.
    virtual std::unique_ptr<domain::User> findByUsername(const std::string& username) = 0;
    virtual void save(const domain::User& user) = 0;
};

}  // namespace lms::data
