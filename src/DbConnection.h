#pragma once

#include "sqlite3.h"

#include <string>

namespace Homework {

    /**
     * A connection to a Sqlite DB. The connection is automatically closed when the instance is deleted.
     */
    class DbConnection {
    public:
        /**
         * Opens the new connection. It is recommended to not use this constructor directly. Please use DataSource::getConnection() instead.
         */
        DbConnection(const std::string& filename);
        DbConnection(const DbConnection&) = delete;
        DbConnection(DbConnection&&);

        DbConnection& operator=(const DbConnection&) = delete;
        DbConnection& operator=(DbConnection&&);

        /**
         * Closes the DB connection.
         */
        ~DbConnection();

        /**
         * @return the handle for executing DB queries
         */
        sqlite3* getHandle();
    private:
        sqlite3* handle = nullptr;
    };
}