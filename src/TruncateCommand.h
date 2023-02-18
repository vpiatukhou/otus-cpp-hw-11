#pragma once

#include "Dao.h"
#include "Request.h"

#include <string>

namespace Homework {

    /**
     * Encapsulates logic of TRUNCATE command.
     */
    class TruncateCommand {
    public:
        TruncateCommand(Dao& dao_);

        std::string operator()(const Request& request);

    private:
        Dao dao;
    };
}
