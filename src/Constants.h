/**
 * Common contants which are used in different parts of the program.
 */
#pragma once

#include <string>
#include <cstdint>

namespace Homework {

    //response codes
    const std::string RESPONSE_OK = "OK\n";
    const std::string RESPONSE_ERR = "ERR ";

    //tables
    const std::string TABLE_A = "A";
    const std::string TABLE_B = "B";

    //positions of arguments in a request
    const std::uint8_t TABLE_ARG_INDEX = 0;
    const std::uint8_t ID_ARG_INDEX = 1;
    const std::uint8_t NAME_ARG_INDEX = 2;
}