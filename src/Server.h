#pragma once

#include "TcpConnection.h"

#include <boost/asio.hpp>

namespace Homework {

    using Port = boost::asio::ip::port_type;

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