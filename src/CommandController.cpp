#include "CommandController.h"
#include "EntityJoinTransformer.h"
#include "InsertCommand.h"
#include "IntersectionCommand.h"
#include "SymmetricDifferenceCommand.h"
#include "TruncateCommand.h"

#include <cstdint>
#include <stdexcept>

namespace Homework {

    namespace {
        const std::string INSERT = "INSERT";
        const std::string TRUNCATE = "TRUNCATE";
        const std::string INTERSECTION = "INTERSECTION";
        const std::string SYMMETRIC_DIFFERENCE = "SYMMETRIC_DIFFERENCE";
    }

    CommandController::CommandController() {
        commands.emplace(INSERT, InsertCommand(dao));
        commands.emplace(TRUNCATE, TruncateCommand(dao));
        commands.emplace(INTERSECTION, IntersectionCommand(dao));
        commands.emplace(SYMMETRIC_DIFFERENCE, SymmetricDifferenceCommand(dao));
    }

    std::string CommandController::execute(const Request& request) {
        if (commands.count(request.commandName)) {
            return commands[request.commandName](request);
        }
        throw std::invalid_argument("Unsupported command '" + request.commandName + "'.");
    }
};