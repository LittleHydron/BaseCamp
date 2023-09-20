#ifndef CONNECTION

#define CONNECTION

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_BUFLEN 512

class Connection {
private:
    WSADATA wsadata;
    SOCKET socketFD;

public:
    Connection() : socketFD(INVALID_SOCKET) {
        if (WSAStartup(MAKEWORD(2, 2), &wsadata)) {
            std::cerr << "WSAStartup failed!" << std::endl;
        }
    }
    bool Initialize(const char *, const char *);
    bool InitializeServer(const char *);
    bool AcceptConnection(void);
    bool Send(const char *);
    bool Receive(char *, int);
    void Close(void);
    ~Connection(void);
};


#endif
