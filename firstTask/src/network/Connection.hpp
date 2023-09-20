#ifndef CONNECTION

#define CONNECTION

#include <iostream>
#include <cstring>

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#else

#include <unistd.h>
#include <netdb.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define SOCKET int

#endif
#define DEFAULT_BUFLEN 512

class Connection {
private:
#ifdef _WIN32
    WSADATA wsadata;
    SOCKET socketFD;
#else
    int socketFD;
#endif
public:
    Connection() : socketFD(INVALID_SOCKET) {
        #ifdef _WIN32
        if (WSAStartup(MAKEWORD(2, 2), &wsadata)) {
            std::cerr << "WSAStartup failed!" << std::endl;
        }
        #endif
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
