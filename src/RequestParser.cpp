#include "RequestParser.h"

#include <algorithm>
#include <vector>
#include <sstream>
#include <utility>

#include <iostream>

namespace Homework {

    namespace {
        const char COMMAND_DELIMITER = '\n';
    }

    void RequestParser::parse(const std::string& rawString) {
        buffer += rawString; //it is possible that the buffer contains a begin of the command and rawString contains the end

        std::size_t lastDelimiterIndex = buffer.find_last_of(COMMAND_DELIMITER);
        if (lastDelimiterIndex != std::string::npos && lastDelimiterIndex > 0) { //there is \n in the given string => the buffer contains the complete command
            std::stringstream commandSequence;
            commandSequence.str(buffer);

            std::string command;
            while (std::getline(commandSequence, command, COMMAND_DELIMITER)) { //there may be more than one command in the rawString
                parseCommandWithParameters(command);
            }

            //we parse the rawString only until the last '\n'. All characters after '\n' are added to the buffer and may be parsed on the next call of parse()
            buffer = lastDelimiterIndex + 1 < rawString.size() ? rawString.substr(lastDelimiterIndex + 1) : "";
        }
    }

    void RequestParser::parseCommandWithParameters(const std::string& command) {
        std::stringstream commandStream(command);

        std::string commandName, argument;
        std::vector<std::string> arguments;

        commandStream >> commandName;
        for (; commandStream >> argument;) {
            arguments.push_back(argument);
        }

        Request request;
        request.commandName = commandName;
        request.arguments = std::move(arguments);

        onRequestReceived(request);
    }
}
