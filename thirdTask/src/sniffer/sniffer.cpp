#include "sniffer.hpp"

void Sniffer::clear_console(void) {
    std::cout << "\033[2J\033[H";
}

void Sniffer::print_protocol_counts(void) {
    clear_console();
    std::cout << "Incoming Protocol Counts:" << std::endl;
    for (const auto &entry : incoming_protocol_counts) {
        if (entry.first != "Other") {
            std::cout << "Protocol " << entry.first << ": " << entry.second << " packets, " << incoming_protocol_summary[entry.first] << " bytes" << std::endl;
        }
    }
    if (incoming_protocol_counts.find("Other") != incoming_protocol_counts.end()) {
        std::cout << "Other protocols: " << incoming_protocol_counts["Other"] << " packets, " << incoming_protocol_summary["Other"] << " bytes" << std::endl;
    }
    std::cout << "\nOutgoing Protocol Counts:" << std::endl;
    for (const auto &entry : outgoing_protocol_counts) {
        if (entry.first != "Other") {
            std::cout << "Protocol " << entry.first << ": " << entry.second << " packets, " << outgoing_protocol_summary[entry.first] << " bytes" << std::endl;
        }
    }
    if (outgoing_protocol_counts.find("Other") != outgoing_protocol_counts.end()) {
        std::cout << "Other protocols: " << outgoing_protocol_counts["Other"] << " packets, " << outgoing_protocol_summary["Other"] << " bytes" << std::endl;
    }
    std::cout << "----------------------" << std::endl;
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
        incoming_protocol_counts[entry.second] = 0;
        outgoing_protocol_counts[entry.second] = 0;
    }
    inet_aton("172.16.183.121", &local_ip_address);
}

void Sniffer::process_packet(const unsigned char *buffer, int size) {
    struct iphdr *ip_header = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    bool is_outgoing = (ip_header->saddr == local_ip_address.s_addr);
    if (protocol_names.find(ip_header->protocol) != protocol_names.end()) {
        if (is_outgoing) {
            ++ outgoing_protocol_counts[protocol_names[ip_header->protocol]];
            outgoing_protocol_summary[protocol_names[ip_header->protocol]] += size;
        } else {
            ++ incoming_protocol_counts[protocol_names[ip_header->protocol]];
            incoming_protocol_summary[protocol_names[ip_header->protocol]] += size;
        }
    } else {
        if (is_outgoing) {
            ++ outgoing_protocol_counts["Other"];
            outgoing_protocol_summary["Other"] += size;
        } else {
            ++ incoming_protocol_counts["Other"];
            incoming_protocol_summary["Other"] += size;
        }
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