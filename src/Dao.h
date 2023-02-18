#pragma once

#include "EntityJoin.h"
#include "DataSource.h"
#include "Entity.h"

#include <stdexcept>
#include <string>
#include <vector>

namespace Homework {

    /**
     * Provides access to the database.
     * 
     * An each instance creates a new connection to the DB.
     * 
     * Please create an instance of Dao per thread.
     */
    class Dao {
    public:
        /**
         * Opens a connection to the database.
         *
         * @throws DatabaseException if it is not possible to connect to the DB.
         */
        Dao();

        /**
         * Closes the connection to the DB.
         */
        ~Dao();

        //void setUpDb();
        void insert(const std::string& tableName, const Entity& entity);
        void truncate(const std::string& tableName);
        std::vector<EntityJoin> intersection();
        std::vector<EntityJoin> symmetricDifference();

    private:
        DataSource& dataSource;

        typedef int (*QueryCallback)(void*, int argc, char** argv, char** azColName);

        std::vector<EntityJoin> selectJoinedEntities(const std::string& sql);
        void executeQuery(const std::string& sql, QueryCallback callback = nullptr, void* callbackParam = nullptr);
    };
}