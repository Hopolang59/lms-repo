#include "domain/User.h"

#include <utility>

namespace lms::domain {

User::User(int id, std::string username, std::string passwordHash, std::string salt, bool active,
           int departmentId)
    : id_(id),
      username_(std::move(username)),
      passwordHash_(std::move(passwordHash)),
      salt_(std::move(salt)),
      active_(active),
      departmentId_(departmentId) {}

}  // namespace lms::domain
