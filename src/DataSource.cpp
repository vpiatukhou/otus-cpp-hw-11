#include "DataSource.h"

#include <string>

namespace Homework {

    const std::string DB_FILENAME = "file::memory:?cache=shared";

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
