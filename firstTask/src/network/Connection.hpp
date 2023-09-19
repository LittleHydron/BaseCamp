#ifndef CONNECTION

#define CONNECTION

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using namespace boost::asio;

class Connection {
private:
    io_service *io;
    ip::tcp::socket *socket;
    ip::tcp::resolver *resolver;
    ip::tcp::acceptor *acceptor;
public:
    Connection(const int);
    Connection(const char *, const char *);
    std::string receive(void);
    void send(const std::string);
    void wait_for(const int);
    ~Connection(void);
};

#endif