#pragma once

#include "Dao.h"
#include "Request.h"

#include <string>
#include <unordered_map>
#include <functional>

namespace Homework {

    class CommandController {
    public:
        CommandController();

        std::string execute(const Request& request);
    private:
        static const std::string INSERT;
        static const std::string TRUNCATE;
        static const std::string INTERSECTION;
        static const std::string SYMMETRIC_DIFFERENCE;

        std::unordered_map<std::string, std::function<std::string(const Request& request)>> commands;

        Dao dao;
    };
};