#pragma once

#include "Dao.h"
#include "Request.h"

#include <string>

namespace Homework {

    /**
     * Encapsulates logic of INTERSECTION command.
     */
    class IntersectionCommand {
    public:
        IntersectionCommand(Dao& dao_);

        std::string operator()(const Request& request);

    private:
        Dao dao;
    };
}
