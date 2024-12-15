#include "add_route.h"
#include <arpa/inet.h>
#include <errno.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

// Create a Netlink socket
int create_netlink_socket() {
    int sockfd = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sockfd < 0) {
        perror("Failed to create Netlink socket");
    }
    return sockfd;
}

// Initialize Netlink message header
struct nlmsghdr *initialize_nlmsghdr() {
    struct nlmsghdr *nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(1024));
    if (!nlh) {
        perror("Failed to allocate memory for nlmsghdr");
        return NULL;
    }
    memset(nlh, 0, NLMSG_SPACE(1024));
    nlh->nlmsg_len = NLMSG_SPACE(1024);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_type = RTM_NEWROUTE;
    nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_CREATE | NLM_F_ACK;
    return nlh;
}

// Initialize routing message
void initialize_rtmsg(struct rtmsg *route_msg, int prefix_len) {
    route_msg->rtm_family = AF_INET;
    route_msg->rtm_dst_len = prefix_len;
    route_msg->rtm_table = RT_TABLE_MAIN;
    route_msg->rtm_protocol = RTPROT_STATIC;
    route_msg->rtm_scope = RT_SCOPE_UNIVERSE;
    route_msg->rtm_type = RTN_UNICAST;
}

// Add an attribute to the Netlink message
void add_rtattr(struct rtattr **rta, int type, const void *data, int data_len) {
    (*rta)->rta_type = type;
    (*rta)->rta_len = RTA_LENGTH(data_len);
    memcpy(RTA_DATA(*rta), data, data_len);
    *rta = (struct rtattr *)(((char *)(*rta)) + RTA_LENGTH(data_len));
}

// Process kernel response
int process_kernel_response(int sockfd) {
    char buffer[8192];
    int len = recv(sockfd, buffer, sizeof(buffer), 0);
    if (len < 0) {
        perror("Failed to receive response from kernel");
        return -1;
    }

    struct nlmsghdr *nlh = (struct nlmsghdr *)buffer;
    if (nlh->nlmsg_type == NLMSG_ERROR) {
        struct nlmsgerr *err = (struct nlmsgerr *)NLMSG_DATA(nlh);
        if (err->error) {
            fprintf(stderr, "Netlink error: %s (code=%d)\n", strerror(-err->error), -err->error);
            return -1;
        }
    }
    return 0;
}

// Add a route to the routing table
int add_route(struct in_addr dest, struct in_addr gateway, int ifindex, int prefix_len) {
    int sockfd = create_netlink_socket();
    if (sockfd < 0) return -1;

    struct sockaddr_nl sa = { .nl_family = AF_NETLINK };

    struct nlmsghdr *nlh = initialize_nlmsghdr();
    if (!nlh) {
        close(sockfd);
        return -1;
    }

    struct rtmsg *route_msg = (struct rtmsg *)NLMSG_DATA(nlh);
    initialize_rtmsg(route_msg, prefix_len);

    struct rtattr *rta = (struct rtattr *)(((char *)route_msg) + NLMSG_ALIGN(sizeof(struct rtmsg)));
    add_rtattr(&rta, RTA_DST, &dest, sizeof(dest));
    add_rtattr(&rta, RTA_GATEWAY, &gateway, sizeof(gateway));
    add_rtattr(&rta, RTA_OIF, &ifindex, sizeof(ifindex));

    if (sendto(sockfd, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        perror("Failed to send Netlink message");
        free(nlh);
        close(sockfd);
        return -1;
    }

    free(nlh);

    if (process_kernel_response(sockfd) < 0) {
        close(sockfd);
        return -1;
    }

    close(sockfd);
    return 0;
}

// Parse IP/Prefix string
int parse_ip_and_prefix(const char *input, struct in_addr *ip, int *prefix) {
    char *slash = strchr(input, '/');
    if (!slash) {
        fprintf(stderr, "Invalid format: %s (expected IP/Prefix)\n", input);
        return -1;
    }

    char ip_str[INET_ADDRSTRLEN];
    strncpy(ip_str, input, slash - input);
    ip_str[slash - input] = '\0';

    if (inet_pton(AF_INET, ip_str, ip) != 1) {
        fprintf(stderr, "Invalid IP address: %s\n", ip_str);
        return -1;
    }

    *prefix = atoi(slash + 1);
    if (*prefix < 0 || *prefix > 32) {
        fprintf(stderr, "Invalid prefix: %s\n", slash + 1);
        return -1;
    }

    return 0;
}

