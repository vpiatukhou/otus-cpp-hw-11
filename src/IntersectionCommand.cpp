#include "IntersectionCommand.h"
#include "Constants.h"
#include "EntityJoinTransformer.h"

namespace Homework {

    IntersectionCommand::IntersectionCommand(Dao& dao_) : dao(dao_) {
    }

    std::string IntersectionCommand::operator()(const Request& request) {
        auto result = dao.intersection();
        auto resultAsStr = transformEntityJoinsToString(result);
        return resultAsStr + RESPONSE_OK;
    }
}
