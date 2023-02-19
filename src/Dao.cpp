#include "Dao.h"
#include "DatabaseException.h"
#include "DbConnection.h"

#include "sqlite3.h"

#include <cstdlib>
#include <cstdint>
#include <iostream>

namespace Homework {

    namespace {
        const std::uint8_t ENTITY_JOIN_ID_INDEX = 0;
        const std::uint8_t ENTITY_JOIN_NAME_A_INDEX = 1;
        const std::uint8_t ENTITY_JOIN_NAME_B_INDEX = 2;
    }

    Dao::Dao() {
    }

    Dao::~Dao() {
    }

    void Dao::insert(const std::string& tableName, const Entity& entity) {
        auto sql = buildInsertSql(tableName, entity);

        DbConnection connection;
        char* errMsg = 0;
        int status = sqlite3_exec(connection.getHandle(), sql.c_str(), nullptr, nullptr, &errMsg);
        if (status == SQLITE_OK) {
            return;
        }
        if (status == SQLITE_CONSTRAINT && SQLITE_CONSTRAINT_PRIMARYKEY == sqlite3_extended_errcode(connection.getHandle())) {
            throw DatabaseException("duplicate " + std::to_string(entity.id));
        }
        if (errMsg != nullptr) {
            std::cerr << "SQL error (" << status << "): " << std::string(errMsg) << std::endl;
            sqlite3_free(errMsg);
        }
        throw DatabaseException("internal error");
    }

    std::string Dao::buildInsertSql(const std::string& tableName, const Entity& entity) {
        std::string sql = "INSERT INTO ";
        sql += tableName;
        sql += "(id, name) VALUES(";
        sql += std::to_string(entity.id);
        sql += ",\'";
        sql += entity.name; //this code is not safe because it allows SQL-injection. But we leave it as it is in order to keep implementation simple
        sql += "\')";
        return sql;
    }

    void Dao::truncate(const std::string& tableName) {
        executeQuery("DELETE FROM " + tableName);
    }

    std::vector<EntityJoin> Dao::intersection() {
        return selectJoinedEntities("SELECT a.id, a.name, b.name FROM a INNER JOIN b ON b.id = a.id");
    }

    std::vector<EntityJoin> Dao::symmetricDifference() {
        return selectJoinedEntities("SELECT * FROM ("
            " SELECT a.id as id, a.name as name_a, NULL AS name_b FROM a"
            " UNION"
            " SELECT b.id as id, NULL AS name_a, b.name AS name_b FROM b"
            " )"
            " WHERE id NOT IN("
            " SELECT a.id AS id2 FROM a INTERSECT SELECT b.id AS id2 FROM b"
            " ) ORDER BY id");
    }

    std::vector<EntityJoin> Dao::selectJoinedEntities(const std::string& sql) {
        std::vector<EntityJoin> result;

        auto callback = [](void* resultPtr, int argc, char** argv, char** azColName) {
            EntityJoin join;
            join.id = std::atoi(argv[ENTITY_JOIN_ID_INDEX]);
            if (argv[ENTITY_JOIN_NAME_A_INDEX] != nullptr) {
                join.nameA = argv[ENTITY_JOIN_NAME_A_INDEX];
            }
            if (argv[ENTITY_JOIN_NAME_B_INDEX] != nullptr) {
                join.nameB = argv[ENTITY_JOIN_NAME_B_INDEX];
            }
                        
            static_cast<std::vector<EntityJoin>*>(resultPtr)->push_back(join);

            return 0;
        };

        executeQuery(sql, callback, &result);
        return result;
    }

    void Dao::executeQuery(const std::string& sql, QueryCallback callback, void* callbackParam) {
        DbConnection connection;

        char* errMsg = 0;
        int status = sqlite3_exec(connection.getHandle(), sql.c_str(), callback, callbackParam, &errMsg);
        if (status != SQLITE_OK) {
            if (errMsg != nullptr) {
                std::cerr << "SQL error (" << status << "): " << std::string(errMsg) << std::endl;
                sqlite3_free(errMsg);
            }
            //we don't want to expose a vendor-specific error message to the client
            throw DatabaseException("internal error");
        }
    }
}