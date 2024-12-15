#include "add_route.h"
#include <arpa/inet.h> // Required for inet_pton
#include <net/if.h>    // Required for if_nametoindex
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <DEST_IP/Prefix> <GATEWAY_IP> <INTERFACE>\n", argv[0]);
        return 1;
    }

    struct in_addr dest, gateway;
    int prefix_len, ifindex;

    if (parse_ip_and_prefix(argv[1], &dest, &prefix_len) < 0) return 1;

    if (inet_pton(AF_INET, argv[2], &gateway) != 1) {
        fprintf(stderr, "Invalid gateway: %s\n", argv[2]);
        return 1;
    }

    ifindex = if_nametoindex(argv[3]);
    if (!ifindex) {
        fprintf(stderr, "Failed to get interface index: %s\n", argv[3]);
        return 1;
    }

    if (add_route(dest, gateway, ifindex, prefix_len) < 0) {
        fprintf(stderr, "Failed to add route\n");
        return 1;
    }

    printf("Route added successfully: %s via %s on interface %s\n", argv[1], argv[2], argv[3]);
    return 0;
}

