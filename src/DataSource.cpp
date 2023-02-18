#include "DataSource.h"

#include <string>

namespace Homework {

    const std::string DB_FILENAME = "../../var/lib/join_server.db";

    DataSource::DataSource() : keepAliveConnection(DB_FILENAME) {
    }

    DbConnection DataSource::getConnection() {
        return DbConnection(DB_FILENAME);
    }

    DataSource& DataSource::getInstance() {
        static DataSource ds;
        return ds;
    }
}
