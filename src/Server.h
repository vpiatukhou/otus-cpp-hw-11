#pragma once

#include "TcpConnection.h"

#include <boost/asio.hpp>

#include <stdint.h>

namespace Homework {

    using Port = std::uint_least16_t;

    class Server {
    public:
        Server(boost::asio::io_context& ioContext_, Port port_);

        void start();

    private:
        Port port;
        boost::asio::ip::tcp::acceptor acceptor;

        void accept();
    };
}