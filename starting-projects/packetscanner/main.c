#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>

// Pseudo header needed for checksum calculation
struct pseudo_header {
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t tcp_length;
};

// Define IP and TCP header sizes
#define IP_HEADER_SIZE 20
#define TCP_HEADER_SIZE 20

// Checksum function to calculate the checksum for IP and TCP headers
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    // Sum all 16-bit words
    for (sum = 0; len > 1; len -= 2) {
        sum += *buf++;
    }

    // Add the last byte, if any
    if (len == 1) {
        sum += *(unsigned char *)buf;
    }

    // Fold the 32-bit sum to 16 bits and return the result
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <Target IP>\n", argv[0]);
        return 1;
    }

    int sock;
    struct sockaddr_in dest;
    char packet[4096];

    // Pointers to the IP and TCP headers within the packet
    struct ip *iph = (struct ip *) packet;  // Changed to struct ip
    struct tcphdr *tcph = (struct tcphdr *) (packet + IP_HEADER_SIZE);
    struct pseudo_header psh;

    // Get the target IP from the command-line argument
    char *target_ip = argv[1];

    // Destination details
    dest.sin_family = AF_INET;
    dest.sin_port = htons(80); // Target port 80 (HTTP)
    dest.sin_addr.s_addr = inet_addr(target_ip); // Set target IP

    // Create a raw socket
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Zero out the packet buffer
    memset(packet, 0, 4096);

    // IP Header setup
    iph->ip_hl = 5; // Set the IP header length (in 32-bit words)
    iph->ip_v = 4;  // Set the IP version to IPv4
    iph->ip_tos = 0;
    iph->ip_len = htons(IP_HEADER_SIZE + TCP_HEADER_SIZE);  // Total length
    iph->ip_id = htonl(54321);  // Random ID
    iph->ip_off = 0;
    iph->ip_ttl = 255; // Max TTL
    iph->ip_p = IPPROTO_TCP; // Protocol type
    iph->ip_sum = 0; // Set to 0 before checksum
    iph->ip_src.s_addr = inet_addr("192.168.1.1"); // Source IP (use any valid source)
    iph->ip_dst.s_addr = dest.sin_addr.s_addr; // Destination IP (target IP)

    // TCP Header setup
    tcph->th_sport = htons(12345); // Random source port
    tcph->th_dport = htons(80); // Destination port (HTTP)
    tcph->th_seq = 0; // Sequence number
    tcph->th_ack = 0; // Acknowledgment number
    tcph->th_x2 = 0; // Unused
    tcph->th_off = 5; // Data offset
    tcph->th_flags = TH_SYN; // SYN flag for initiating a handshake
    tcph->th_win = htons(5840); // Window size
    tcph->th_sum = 0; // Leave checksum 0 now, calculate it later
    tcph->th_urp = 0; // Urgent pointer

    // Pseudo header setup (needed for TCP checksum calculation)
    psh.source_address = inet_addr("192.168.1.1"); // Source IP
    psh.dest_address = dest.sin_addr.s_addr; // Destination IP
    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP; // Protocol type
    psh.tcp_length = htons(TCP_HEADER_SIZE); // TCP header length

    // Calculate size of pseudo header + TCP header
    int psize = sizeof(struct pseudo_header) + sizeof(struct tcphdr);
    char *pseudogram = malloc(psize);

    // Copy pseudo header and TCP header to the pseudogram buffer
    memcpy(pseudogram, (char *)&psh, sizeof(struct pseudo_header));
    memcpy(pseudogram + sizeof(struct pseudo_header), tcph, sizeof(struct tcphdr));

    // Calculate the checksum for the TCP header
    tcph->th_sum = checksum((unsigned short *)pseudogram, psize);

    // Calculate the checksum for the IP header
    iph->ip_sum = checksum((unsigned short *)packet, IP_HEADER_SIZE);

    // Send the packet using the socket
    if (sendto(sock, packet, iph->ip_len, 0, (struct sockaddr *)&dest, sizeof(dest)) < 0) {
        perror("Send failed");
    }

    close(sock); // Close the socket
    free(pseudogram); // Free the allocated memory for pseudogram

    return 0;
}
