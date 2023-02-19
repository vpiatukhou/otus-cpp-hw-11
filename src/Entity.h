#pragma once

#include <string>

namespace Homework {

    /**
     * Represents a DB table.
     */
    struct Entity {
        int id;
        std::string name;
    };

}