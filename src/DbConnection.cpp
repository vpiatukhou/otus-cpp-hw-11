#include "DbConnection.h"
#include "DatabaseException.h"

#include <string>
#include <iostream>

namespace Homework {

    namespace {
        const std::string DB_FILEPATH = "/usr/var/lib/join_server.db";
    }

    DbConnection::DbConnection() {
        int status = sqlite3_open(DB_FILEPATH.c_str(), &handle);
        if (status != SQLITE_OK) {
            std::string msg = "Cannot open the database. Please make sure that the file '" + DB_FILEPATH + "' exists. Sqlite status: "
                + std::to_string(status) + ". Message: " + sqlite3_errmsg(handle);
            sqlite3_close(handle);

            throw DatabaseException(msg);
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