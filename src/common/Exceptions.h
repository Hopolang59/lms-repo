#pragma once
#include <stdexcept>
#include <string>

namespace lms {

// Base class for every error the program raises on purpose.
// The console UI catches LmsException, shows what() and returns to the menu (NFR-05).
class LmsException : public std::runtime_error {
public:
    explicit LmsException(const std::string& message) : std::runtime_error(message) {}
};

class ValidationError : public LmsException {
public:
    using LmsException::LmsException;
};

class AuthorisationError : public LmsException {
public:
    using LmsException::LmsException;
};

class NotFoundError : public LmsException {
public:
    using LmsException::LmsException;
};

class DatabaseError : public LmsException {
public:
    using LmsException::LmsException;
};

}  // namespace lms
