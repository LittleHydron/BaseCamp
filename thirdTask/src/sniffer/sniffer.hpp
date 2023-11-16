#ifndef SNIFFER_HPP

#define SNIFFER_HPP

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <map>

#define MAX_PACKET_SIZE 65536

class Sniffer {
    int raw_socket;
    std::map<int, std::string> protocol_names;
    std::map<std::string, int> total_protocol_counts;
    std::map<std::string, uint64_t> total_protocol_summary;
    void clear_console(void);
    void print_protocol_counts(void);
public:
    Sniffer(void);
    void process_packet(const unsigned char *, int);
    void run(void);
};


#endif