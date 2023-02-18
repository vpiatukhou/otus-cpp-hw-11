#pragma once

#include "EntityJoin.h"

#include <vector>
#include <string>

namespace Homework {

    /**
     * Transforms the given objects to a string.
     *
     * @result a string representation of the given objects
     */
    std::string transformEntityJoinsToString(const std::vector<EntityJoin>& combinations);
}
