#pragma once

#include "sqlite3.h"

namespace Homework {

    /**
     * A connection to a Sqlite DB. An each instance of the class is a separate connection.
     */
    class DbConnection {
    public:
        /**
         * Opens the new connection. The connection will be automatically closed when the instance is destroyed.
         */
        DbConnection();
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