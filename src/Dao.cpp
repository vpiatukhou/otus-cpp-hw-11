#include "Dao.h"
#include "DatabaseException.h"

#include "sqlite3.h"

#include <cstdlib>
#include <iostream> //TODO remove

namespace Homework {
    /*
    class Connection {
    public:
        sqlite3* handle;

        Connection() {
            int error = sqlite3_open(":memory:", &handle);
            if (error) {
                sqlite3_close(handle);

                using namespace std::string_literals;
                throw DatabaseException("Cannot open database: "s + sqlite3_errmsg(handle));
            }
        }

        ~Connection() {
            if (handle != nullptr) {
                sqlite3_close(handle);
            }
        }
    };

    Connection connection;*/

    Dao::Dao() : dataSource(DataSource::getInstance()) {
    }

    Dao::~Dao() {
    }
    /*
    void Dao::setUpDb() {
        executeQuery("CREATE TABLE a(id INTEGER PRIMARY KEY, name VARCHAR(100))");
        executeQuery("CREATE TABLE b(id INTEGER PRIMARY KEY, name VARCHAR(100))");
    }*/

    void Dao::insert(const std::string& tableName, const Entity& entity) {
        auto idAsStr = std::to_string(entity.id);

        std::string sql = "INSERT INTO ";
        sql += tableName;
        sql += "(id, name) VALUES(";
        sql += idAsStr;
        sql += ",\'";
        sql += entity.name; //TODO is it possible to avoid SQL injection?
        sql += "\')";
        //TODO handle error if duplicate primary key

        DbConnection connection = dataSource.getConnection();

        std::cout << "Executing query: " << sql << std::endl;

        char* errMsg = 0;
        int status = sqlite3_exec(connection.getHandle(), sql.c_str(), nullptr, nullptr, &errMsg);
        
        std::cout << "Query result code: " << status << std::endl;

        if (status == SQLITE_OK) {
            return;
        }

        if (status == SQLITE_CONSTRAINT && SQLITE_CONSTRAINT_PRIMARYKEY == sqlite3_extended_errcode(connection.getHandle())) {
            throw DatabaseException("duplicate " + idAsStr);
        }
        std::string msg = "SQL error (" + std::to_string(status) + ")";
        if (errMsg != nullptr) {
            msg += ": " + std::string(errMsg);
            sqlite3_free(errMsg);
        }
        throw DatabaseException("internal error");
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
            join.id = std::atoi(argv[0]);
            if (argv[1] != nullptr) {
                join.nameA = argv[1];
            }
            if (argv[2] != nullptr) {
                join.nameB = argv[2];
            }
                        
            static_cast<std::vector<EntityJoin>*>(resultPtr)->push_back(join);

            return 0;
        };

        executeQuery(sql, callback, &result);
        return result;
    }

    void Dao::executeQuery(const std::string& sql, QueryCallback callback, void* callbackParam) {
        DbConnection connection = dataSource.getConnection();

        std::cout << "Executing query: " << sql << std::endl;

        char* errMsg = 0;
        int status = sqlite3_exec(connection.getHandle(), sql.c_str(), callback, callbackParam, &errMsg);
        if (status != SQLITE_OK) {
            std::string msg = "SQL error (" + std::to_string(status) + ")";
            if (errMsg != nullptr) {
                msg += ": " + std::string(errMsg);
                std::cerr << "Error occurred during execution of query'" << sql << "': " << msg << std::endl;
                sqlite3_free(errMsg);
            }
            //we don't want to expose a vendor-specific error message to the client
            throw DatabaseException("internal error");
        }
    }
}