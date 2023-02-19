#include "RequestParser.h"

#include <sstream>

namespace Homework {

    namespace {
        const char COMMAND_DELIMITER = '\n';
    }

    void RequestParser::parse(const std::string& rawString) {
        buffer += rawString; //it is possible that the buffer contains a begin of the command and rawString contains the end

        std::size_t lastDelimiterIndex = buffer.find_last_of(COMMAND_DELIMITER);
        if (lastDelimiterIndex != std::string::npos && lastDelimiterIndex > 0) { //there is \n in the given string => the buffer contains the complete command
            std::istringstream commandSequence;
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
        std::istringstream stream(command);

        std::string token;
        stream >> token;

        Request request;
        request.commandName = token;

        for (; stream >> token;) {
            request.arguments.push_back(token);
        }

        onRequestReceived(request);
    }
}
