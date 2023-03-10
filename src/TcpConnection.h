#pragma once

#include "CommandController.h"
#include "RequestParser.h"

#include <boost/asio.hpp>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace Homework {

    /**
     * A TCP connection. Receives commands from a client, forwards them to CommandController and sends response back to client.
     * 
     * The connection stays open until the client breaks it.
     */
    class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
    public:
        TcpConnection(boost::asio::ip::tcp::socket& socket_);

        void listen();

    private:
        static constexpr std::uint8_t REQUEST_DATA_BLOCK_SIZE_BYTES = 255;
        
        boost::asio::ip::tcp::socket socket;
        
        std::array<char, REQUEST_DATA_BLOCK_SIZE_BYTES> request;
        std::string response;

        RequestParser parser;
        CommandController commandController;

        void writeResponse();
    };

}

