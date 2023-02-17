#pragma once

#include <stdexcept>
#include <string>

namespace Homework {

    /**
     * Thrown in case of an error during interaction with the database.
     */
    class DatabaseException : public std::runtime_error {
    public:
        DatabaseException(const std::string& message) : std::runtime_error(message) {
        }
    };

}
