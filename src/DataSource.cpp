#include "DataSource.h"

#include <string>

namespace Homework {

    namespace {
        const std::string DB_FILEPATH = "/usr/var/lib/join_server.db";
    }

    DataSource::DataSource() : keepAliveConnection(DB_FILEPATH) {
    }

    DbConnection DataSource::getConnection() {
        return DbConnection(DB_FILEPATH);
    }

    DataSource& DataSource::getInstance() {
        static DataSource ds;
        return ds;
    }
}
