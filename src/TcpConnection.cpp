#include "TcpConnection.h"
#include "Constants.h"

#include <iostream>
#include <stdexcept>

namespace Homework {

    TcpConnection::TcpConnection(boost::asio::ip::tcp::socket& socket_) : socket(std::move(socket_)) {
        parser.onRequestReceived = [this](const Request& command) {
            try {
                response = commandController.execute(command);
            } catch (std::exception& e) {
                response = RESPONSE_ERR + e.what() + '\n';
            }

            writeResponse();
        };
    }

    void TcpConnection::listen() {
        //pass "self" to the callback in order to keep the instance of TcpConnection alive while the connection exists
        auto self = shared_from_this();
        socket.async_read_some(boost::asio::buffer(request, REQUEST_DATA_BLOCK_SIZE_BYTES),
            [this, self](boost::system::error_code error, std::size_t bytesTransferred) {

            if (error) {
                //if the connection hasn't been closed by the client, print an error
                if (error != boost::asio::error::eof && error != boost::asio::error::connection_reset) { 
                    std::cerr << "Error reading request. Code: " << error << " Message: " << error.message() << std::endl;
                }
            } else {
                if (bytesTransferred > 0) {
                    std::string toParse(request.data(), bytesTransferred);

                    try {
                        parser.parse(toParse);
                    } catch (std::exception& e) {
                        std::cerr << "Error parsing '" << toParse << "': " << e.what() << std::endl;
                        response = "Invalid input.";
                        writeResponse();
                    }
                }

                listen();
            }
        });
    }

    void TcpConnection::writeResponse() {
        boost::asio::async_write(socket, boost::asio::buffer(response), [this](boost::system::error_code error, std::size_t bytesTransferred) {

            response = ""; //reset the variable after the response is sent
            if (error) {
                std::cerr << "Error writing response. Code: " << error << " Message: " << error.message() << std::endl;
            }
            });
    }
}

