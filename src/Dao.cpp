#include "Dao.h"
#include "DatabaseException.h"

#include "sqlite3.h"

#include <cstdlib>

namespace Homework {

    Dao::Dao() : dataSource(DataSource::getInstance()) {
    }

    Dao::~Dao() {
    }

    void Dao::setUpDb() {
        executeQuery("CREATE TABLE a(id INTEGER PRIMARY KEY, name VARCHAR(100));CREATE TABLE b(id INTEGER PRIMARY KEY, name VARCHAR(100));");
    }

    void Dao::insert(const std::string& tableName, const Entity& entity) {
        std::string sql = "INSERT INTO ";
        sql += tableName;
        sql += "(id, name) VALUES(";
        sql += std::to_string(entity.id);
        sql += ",\'";
        sql += entity.name; //TODO is it possible to avoid SQL injection?
        sql += "\')";
        //TODO handle error if duplicate primary key
        executeQuery(sql);
    }

    void Dao::truncate(const std::string& tableName) {
        executeQuery("DELETE FROM " + tableName);
    }

    std::vector<Combination> Dao::intersection() {
        return selectCombindations("SELECT a.id, a.name, b.name FROM a INNER JOIN b ON b.id = a.id");
    }

    std::vector<Combination> Dao::symmetricDifference() {
        return selectCombindations("SELECT * FROM ("
            " SELECT a.id as id, a.name as name_a, NULL AS name_b FROM a"
            " UNION"
            " SELECT b.id as id, NULL AS name_a, b.name AS name_b FROM b"
            " )"
            " WHERE id NOT IN("
            " SELECT a.id AS id2 FROM a INTERSECT SELECT b.id AS id2 FROM b"
            " ) ORDER BY id");
    }

    std::vector<Combination> Dao::selectCombindations(const std::string& sql) {
        std::vector<Combination> result;

        auto callback = [](void* resultPtr, int argc, char** argv, char** azColName) {
            Combination combindation;
            combindation.id = std::atoi(argv[0]);
            if (argv[1] != nullptr) {
                combindation.nameA = argv[1];
            }
            if (argv[2] != nullptr) {
                combindation.nameB = argv[2];
            }
                        
            static_cast<std::vector<Combination>*>(resultPtr)->push_back(combindation);

            return 0;
        };

        executeQuery(sql, callback, &result);
        return result;
    }

    void Dao::executeQuery(const std::string& sql, QueryCallback callback, void* callbackParam) {
        DbConnection connection = dataSource.getConnection();

        char* errMsg = 0;
        int status = sqlite3_exec(connection.getHandle(), sql.c_str(), callback, callbackParam, &errMsg);
        if (status != SQLITE_OK) {
            std::string msg = "SQL error: ";
            msg += std::string(errMsg);
            sqlite3_free(errMsg);
            throw DatabaseException(msg);
        }
    }
}