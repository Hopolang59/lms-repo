#pragma once
#include <string>

#include "domain/Action.h"
#include "domain/Role.h"

namespace lms::domain {

// Abstract base class for the four roles. Polymorphism is used for role behaviour:
// each subclass says which role it is and which actions it allows.
class User {
public:
    User(int id, std::string username, std::string passwordHash, std::string salt, bool active,
         int departmentId);
    virtual ~User() = default;

    int getId() const { return id_; }
    const std::string& getUsername() const { return username_; }
    const std::string& getPasswordHash() const { return passwordHash_; }
    const std::string& getSalt() const { return salt_; }
    bool isActive() const { return active_; }
    int getDepartmentId() const { return departmentId_; }  // 0 when the user has no department

    virtual Role role() const = 0;
    virtual bool canPerform(Action action) const = 0;

private:
    int id_;
    std::string username_;
    std::string passwordHash_;
    std::string salt_;
    bool active_;
    int departmentId_;
};

}  // namespace lms::domain
