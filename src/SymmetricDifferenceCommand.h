#pragma once

#include "Dao.h"
#include "Request.h"

#include <string>

namespace Homework {

    /**
     * Encapsulates logic of SYMMETRIC_DIFFERENCES command.
     */
    class SymmetricDifferenceCommand {
    public:
        SymmetricDifferenceCommand(Dao& dao_);

        std::string operator()(const Request& request);

    private:
        Dao dao;
    };
}
