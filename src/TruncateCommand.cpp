#include "TruncateCommand.h"
#include "Constants.h"

#include <cstdint>
#include <stdexcept>

namespace Homework {

    namespace {
        const std::uint8_t NUMBER_OF_ARGS_TRUNCATE = 1;
    }

    TruncateCommand::TruncateCommand(Dao& dao_) : dao(dao_) {
    }

    std::string TruncateCommand::operator()(const Request& request) {
        if (request.arguments.size() != NUMBER_OF_ARGS_TRUNCATE) {
            throw std::invalid_argument("Wrong number of arguments.");
        }
        auto tableName = request.arguments[TABLE_ARG_INDEX];
        if (tableName != TABLE_A && tableName != TABLE_B) {
            throw std::invalid_argument("Unknown table '" + tableName + "'.");
        }
        dao.truncate(tableName);
        return RESPONSE_OK;
    }
}
