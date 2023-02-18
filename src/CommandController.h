#pragma once

#include "Dao.h"
#include "Request.h"

#include <string>
#include <functional>
#include <unordered_map>

namespace Homework {

    /**
     * Consumes a parsed request, validates it and call appropriate DAO method.
     */
    class CommandController {
    public:
        CommandController();

        std::string execute(const Request& request);
    private:
        std::unordered_map<std::string, std::function<std::string(const Request& request)>> commands;

        Dao dao;
    };
};