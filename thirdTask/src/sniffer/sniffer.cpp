#include "sniffer.hpp"

void Sniffer::clear_console(void) {
    std::cout << "\033[2J\033[H";
}

void Sniffer::print_protocol_counts(void) {
    clear_console();
    std::cout << "Total Protocol Counts:" << std::endl;
    for (const auto &entry : total_protocol_counts) {
        if (entry.first != "Other") {
            std::cout << "Protocol " << entry.first << ": " << entry.second << " packets, " << total_protocol_summary[entry.first] << " bytes" << std::endl;
        }
    }
    if (total_protocol_counts.find("Other") != total_protocol_counts.end()) {
        std::cout << "Other protocols: " << total_protocol_counts["Other"] << " packets, " << total_protocol_summary["Other"] << " bytes" << std::endl;
    }
}

Sniffer::Sniffer(void) : raw_socket(socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) {
    if (raw_socket == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }
    protocol_names[IPPROTO_TCP] = "TCP";
    protocol_names[IPPROTO_UDP] = "UDP";
    protocol_names[IPPROTO_ICMP] = "ICMP";
    for (const auto &entry : protocol_names) {
        total_protocol_counts[entry.second] = 0;
        total_protocol_counts[entry.second] = 0;
    }
}

void Sniffer::process_packet(const unsigned char *buffer, int size) {
    struct iphdr *ip_header = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    if (protocol_names.find(ip_header->protocol) != protocol_names.end()) {
            ++ total_protocol_counts[protocol_names[ip_header->protocol]];
            total_protocol_summary[protocol_names[ip_header->protocol]] += size;
    } else {
            ++ total_protocol_counts["Other"];
            total_protocol_summary["Other"] += size;
    }
    print_protocol_counts();
}

void Sniffer::run(void) {
    unsigned char buffer[MAX_PACKET_SIZE];
    while (true) {
        int data_size = recv(raw_socket, buffer, sizeof(buffer), 0);
        if (data_size < 0) {
            perror("Packet receive error");
            close(raw_socket);
            exit(EXIT_FAILURE);
        }

        process_packet(buffer, data_size);
    }

    close(raw_socket);
}