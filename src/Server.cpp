#include "Server.h"

#include <boost/asio.hpp>

#include <iostream> //TODO to remove

namespace Homework {

    using namespace boost::asio::ip;

    Server::Server(boost::asio::io_context& ioContext_, Port port_) : port(port_),
        acceptor(ioContext_, tcp::endpoint(tcp::v4(), port)) {
    }

    void Server::start() {
        accept();
    }

    void Server::accept() {
        acceptor.async_accept([this](boost::system::error_code error, boost::asio::ip::tcp::socket socket) {

            if (error) {
                std::cout << "Acception error: " << error << " " << error.what() << std::endl; //TODO add error handling
            } else {
                //Make a shared pointer in order to allow usage enable_shared_from_this in TcpConnection.
                //The instance of TcpConnection won't be deleted when "accept()" returns control because the pointer to it will be "catched" in TcpConnection::listen().
                std::make_shared<TcpConnection>(socket)->listen();

                accept();
            }

            });
    }
}