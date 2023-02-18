//#include "Dao.h"
#include "Server.h"

#include <cctype>
#include <iostream>
#include <stdexcept>

namespace Homework {

    namespace {
        const int UNEXPECTED_ERROR = -1;
        const int VALIDATION_ERROR = -2;

        const Port MAX_PORT = 65535;

        const std::string INVALID_PORT = "A port must be in the range [0-" + std::to_string(MAX_PORT) + "].";
    }

    Port stringToPort(const std::string& portAsStr) {
        if (portAsStr.size() > std::to_string(MAX_PORT).size()) {
            throw std::invalid_argument(INVALID_PORT);
        }
        for (auto c : portAsStr) {
            if (!std::isdigit(c)) {
                throw std::invalid_argument(INVALID_PORT);
            }
        }
        long number = std::stoul(portAsStr);
        if (number > MAX_PORT) {
            throw std::invalid_argument(INVALID_PORT);
        }
        return static_cast<Port>(number);
    }
}

int main(int argc, char* argv[]) {
    using namespace Homework;

    //validate input
    if (argc < 2) {
        std::cerr << "Please provide a port." << std::endl;
        return VALIDATION_ERROR;
    }

    Port port;
    try {
        port = stringToPort(argv[1]);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return VALIDATION_ERROR;
    }

    try {
        //set up the DB
        /*{
            std::cout << "Creating a database..." << std::endl;

            //Dao dao;
            //dao.setUpDb();

            std::cout << "The database was created." << std::endl;
        }*/

        std::cout << "Starting the server..." << std::endl;

        //start the server
        boost::asio::io_context ioContext;
        
        Server server(ioContext, port);
        server.start();

        std::cout << "The server is listening on the port " << port << '.' << std::endl;

        ioContext.run();
    } catch (std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return UNEXPECTED_ERROR;
    }

    return 0;
}
