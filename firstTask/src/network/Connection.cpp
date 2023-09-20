#include "Connection.hpp"

bool Connection::Initialize(const char* serverIP, const char* serverPort) {
    struct addrinfo *result = nullptr, *ptr = nullptr, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int iResult = getaddrinfo(serverIP, serverPort, &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed: " << iResult << std::endl;
        return false;
    }

    ptr = result;
    socketFD = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (socketFD == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        return false;
    }

    iResult = connect(socketFD, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen));
    freeaddrinfo(result);

    if (iResult == SOCKET_ERROR) {
        std::cerr << "Unable to connect to server!" << std::endl;
        Close();
        return false;
    }

    return true;
}

bool Connection::InitializeServer(const char* port) {
    struct addrinfo *result = nullptr, *ptr = nullptr, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    int iResult = getaddrinfo(NULL, port, &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed: " << iResult << std::endl;
        return false;
    }

    ptr = result;
    socketFD = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (socketFD == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        return false;
    }

    iResult = bind(socketFD, ptr->ai_addr, (int)ptr->ai_addrlen);
    freeaddrinfo(result);

    if (iResult == SOCKET_ERROR) {
        std::cerr << "bind failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }

    if (listen(socketFD, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }

    return true;
}

bool Connection::AcceptConnection(void) {
    SOCKET ClientSocket = accept(socketFD, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }

    socketFD = ClientSocket;
    return true;
}

bool Connection::Send(const char* message) {
    int iResult = send(socketFD, message, static_cast<int>(strlen(message)), 0);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "send failed: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

bool Connection::Receive(char* buffer, int bufferSize) {
    int iResult = recv(socketFD, buffer, bufferSize, 0);
    if (iResult > 0) {
        buffer[iResult] = '\0'; // Null-terminate the received data
        return true;
    } else if (iResult == 0) {
        std::cerr << "Connection closed by server." << std::endl;
    } else {
        std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
    }
    return false;
}

void Connection::Close(void) {
    if (socketFD != INVALID_SOCKET) {
        closesocket(socketFD);
        socketFD = INVALID_SOCKET;
    }
}

Connection::~Connection(void) {
    Close();
    WSACleanup();
}
