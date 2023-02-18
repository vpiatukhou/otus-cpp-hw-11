#include "DbConnection.h"
#include "DatabaseException.h"

#include <iostream>

namespace Homework {

    DbConnection::DbConnection(const std::string& filename) {
        std::cerr << "Opening the DB." << std::endl;

        int error = sqlite3_open(filename.c_str(), &handle);
        if (error) {
            std::cerr << "Error opening DB. Code: " << error << ". Message: " << sqlite3_errmsg(handle) << std::endl;

            sqlite3_close(handle);

            throw DatabaseException("Cannot open database. Please make sure that the file '" + filename + "' exists.");
        }
    }

    DbConnection::DbConnection(DbConnection&& other) {
        handle = other.handle;
        other.handle = nullptr;
    }

    DbConnection& DbConnection::operator=(DbConnection&& other) {
        handle = other.handle;
        other.handle = nullptr;
        return *this;
    }

    DbConnection::~DbConnection() {
        std::cout << "Destroying the connection." << std::endl;
        if (handle != nullptr) {
            std::cout << "Closing the DB." << std::endl;
            sqlite3_close(handle);
        }
    }

    sqlite3* DbConnection::getHandle() {
        return handle;
    }
}