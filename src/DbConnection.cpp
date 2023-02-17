#include "DbConnection.h"
#include "DatabaseException.h"

namespace Homework {

    DbConnection::DbConnection(const std::string& filename) {
        sqlite3* handle;
        //create an in-memory which can be shared between multiple connections
        int error = sqlite3_open(filename.c_str(), &handle);
        if (error) {
            sqlite3_close(handle);

            using namespace std::string_literals;
            throw DatabaseException("Cannot open database: "s + sqlite3_errmsg(handle));
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
        if (handle != nullptr) {
            sqlite3_close(handle);
        }
    }

    sqlite3* DbConnection::getHandle() {
        return handle;
    }
}