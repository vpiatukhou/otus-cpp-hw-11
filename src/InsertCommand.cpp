#include "InsertCommand.h"
#include "Constants.h"
#include "Entity.h"

#include <cstdint>
#include <stdexcept>
#include <limits>

namespace Homework {

    namespace {
        const std::uint8_t NUMBER_OF_ARGS_INSERT = 3;
        const std::uint8_t NAME_ARG_SIZE = 100;
    }

    InsertCommand::InsertCommand(Dao& dao_) : dao(dao_) {
    }

    std::string InsertCommand::operator()(const Request& request) {
        if (request.arguments.size() != NUMBER_OF_ARGS_INSERT) {
            throw std::invalid_argument("Wrong number of arguments. The format of the command is: INSERT tableName id name");
        }

        auto tableName = request.arguments[TABLE_ARG_INDEX];
        if (tableName != TABLE_A && tableName != TABLE_B) {
            throw std::invalid_argument("Unknown table '" + tableName + "'.");
        }

        Entity entity;
        try {
            entity.id = std::stoi(request.arguments[ID_ARG_INDEX]);
        } catch (std::exception& e) {
            std::string msg = "ID must be an integer number in the range ["
                + std::to_string(std::numeric_limits<int>::min()) + " - "
                + std::to_string(std::numeric_limits<int>::max()) + "].";
            throw std::invalid_argument(msg);
        }
        auto name = request.arguments[NAME_ARG_INDEX];
        if (name.size() > NAME_ARG_SIZE) {
            throw std::invalid_argument("Param 'name' must not exceed " + std::to_string(NAME_ARG_SIZE) + " characters.");
        }

        entity.name = name;
        dao.insert(tableName, entity);
        return RESPONSE_OK;
    }
}
