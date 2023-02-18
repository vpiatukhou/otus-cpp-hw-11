#include "SymmetricDifferenceCommand.h"
#include "Constants.h"
#include "EntityJoinTransformer.h"

namespace Homework {

    SymmetricDifferenceCommand::SymmetricDifferenceCommand(Dao& dao_) : dao(dao_) {
    }

    std::string SymmetricDifferenceCommand::operator()(const Request& request) {
        auto result = dao.symmetricDifference();
        auto resultAsStr = transformEntityJoinsToString(result);
        return resultAsStr + RESPONSE_OK;
    }
}
