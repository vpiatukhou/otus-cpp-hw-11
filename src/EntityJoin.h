#pragma once

#include <string>

namespace Homework {

    /**
     * Represents a join of records from two tables.
     */
    struct EntityJoin {
        int id;
        std::string nameA;
        std::string nameB;
    };

}