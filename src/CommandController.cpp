#include "CombinationTransformer.h"
#include "CommandController.h"

#include <stdexcept>

namespace Homework {

    const std::string CommandController::INSERT = "INSERT";
    const std::string CommandController::TRUNCATE = "TRUNCATE";
    const std::string CommandController::INTERSECTION = "INTERSECTION";
    const std::string CommandController::SYMMETRIC_DIFFERENCE = "SYMMETRIC_DIFFERENCE";

    const std::string RESPONSE_OK = "OK\n";

    CommandController::CommandController() {
        //In a real-life application, a separate class would be used for an each command instead of lambdas.
        //It was decided to use lambdas in order to make the code more clear
        commands.emplace(INSERT, [this](const Request& request) {
            if (request.arguments.size() != 3) {
                throw std::invalid_argument("Invalid number of arguments");
            }

            Entity table;
            table.id = std::stoi(request.arguments[1]);
            table.name = request.arguments[2];
            dao.insert(request.arguments[0], table);
            return RESPONSE_OK;
            });

        commands.emplace(TRUNCATE, [this](const Request& request) {
            if (request.arguments.size() != 1) {
                throw std::invalid_argument("Invalid number of arguments");
            }
            dao.truncate(request.arguments[0]);
            return RESPONSE_OK;
            });

        commands.emplace(INTERSECTION, [this](const Request& request) {
            auto result = dao.intersection();
            auto resultAsStr = transformCombinationToString(result);
            return resultAsStr + RESPONSE_OK;
            });

        commands.emplace(SYMMETRIC_DIFFERENCE, [this](const Request& request) {
            auto result = dao.symmetricDifference();
            auto resultAsStr = transformCombinationToString(result);
            return resultAsStr + RESPONSE_OK;
            });
    }

    std::string CommandController::execute(const Request& request) {
        if (commands.count(request.commandName)) {
            return commands[request.commandName](request);
        }
        throw std::invalid_argument("Unsupported command '" + request.commandName + "'");
    }
};