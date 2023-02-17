#pragma once

#include <string>
#include <vector>

namespace Homework {

    /**
     * A request, sent by a client.
     */
    struct Request {
        std::string commandName;
        std::vector<std::string> arguments;
    };

}