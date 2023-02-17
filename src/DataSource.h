#pragma once

#include "DbConnection.h"

namespace Homework {

    /**
     * Creates connections to the DB.
     * 
     * The DB is created in memory and deleted when the last connection is closed.
     * 
     * Please see DbConnection and "keepAliveConnection".
     */
    class DataSource {
    public:
        DataSource(const DataSource&) = delete;
        DataSource(DataSource&&) = delete;
        ~DataSource() = default;

        DataSource& operator=(const DataSource&) = delete;
        DataSource& operator=(DataSource&&) = delete;

        DbConnection getConnection();

        static DataSource& getInstance();
    private:
        DataSource();

        //This connection is not used directly. The in-memory DB exists while there is at least one connection.
        //This connection ensures that the DB won't be deleted until the application is shut down
        DbConnection keepAliveConnection;
    };
}