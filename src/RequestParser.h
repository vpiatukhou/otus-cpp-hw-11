#pragma once

#include "Request.h"

#include <functional>
#include <string>

namespace Homework {

    /**
     * Parses the given request.
     */
    class RequestParser {
    public:
        /**
         * Parses the given raw string and builds a Request object.
         * 
         * @param rawRequest - a request as a raw string. It may contain:
         *
         *                     1. A single command, ended with '\n'. E.g.:
         * 
         *                     INSERT tableName value\n
         * 
         *                     2. Multiple commands. E.g.:
         * 
         *                     INSERT tableName value\nTRUNCATE tableName\nINTERSECTION\n
         * 
         *                     3. A part of a command
         * 
         *                     INSER
         * 
         *                     In the last case the given string will be added to the buffer and will be parsed after remained parts have been added.
         */
        void parse(const std::string& rawString);

        /**
         * A callback function which is called after the request is parsed.
         * 
         * @param request - the resulted request object
         */
        std::function<void(const Request& request)> onRequestReceived;

    private:
        std::string buffer;

        /**
         * Parses the given command and call onRequestReceived().
         * 
         * @param commandWithParams - e.g.: "INSERT tableName value\n"
         */
        void parseCommandWithParameters(const std::string& commandWithParams);
    };
}
