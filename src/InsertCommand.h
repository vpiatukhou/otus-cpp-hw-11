#pragma once

#include "Dao.h"
#include "Request.h"

#include <string>

namespace Homework {

    /**
     * Encapsulates logic of INSERT command.
     */
    class InsertCommand {
    public:
        InsertCommand(Dao& dao_);

        std::string operator()(const Request& request);
    private:
        Dao dao;
    };
}
