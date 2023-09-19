#include "Connection.hpp"

Connection::Connection(const int port) {
    io = new io_service();
    socket = new ip::tcp::socket(*io);
    acceptor = new ip::tcp::acceptor(*io, ip::tcp::endpoint(ip::tcp::v4(), port));
    (*acceptor).accept(*socket);
}

Connection::Connection(const char *ip, const char *port) {
    io = new io_service();
    socket = new ip::tcp::socket(*io);
    resolver = new ip::tcp::resolver(*io);
    connect(*socket, resolver->resolve({ip, port}));
}

std::string Connection::receive(void) {
    boost::system::error_code error;
    std::array<char, 1024> buffer = {};
    size_t length = socket->read_some(boost::asio::mutable_buffer(buffer.data(), buffer.size()), error);

    if (error) {
        throw boost::system::system_error(error);
    }

    return std::string(buffer.data(), length);
}

void Connection::send(const std::string message) {
    boost::system::error_code error;
    boost::asio::write(*socket, boost::asio::buffer(message), error);
    if (error) {
        throw boost::system::system_error(error);
    }
}

void Connection::wait_for(const int seconds) {
    boost::asio::deadline_timer timer(*io, boost::posix_time::seconds(seconds));
    timer.wait();
}

Connection::~Connection(void) {
    if (io) {
        delete io;
    }
    if (socket) {
        delete socket;
    }
    if (resolver) {
        delete resolver;
    }
    if (acceptor) {
        delete acceptor;
    }
}
