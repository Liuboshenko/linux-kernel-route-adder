#ifndef ADD_ROUTE_H
#define ADD_ROUTE_H

#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <netinet/in.h>

/**
 * Create a Netlink socket.
 * @return File descriptor of the socket, or -1 on error.
 */
int create_netlink_socket();

/**
 * Initialize a Netlink message header.
 * @return Pointer to the initialized nlmsghdr, or NULL on error.
 */
struct nlmsghdr *initialize_nlmsghdr();

/**
 * Initialize a routing message.
 * @param route_msg Pointer to the rtmsg structure.
 * @param prefix_len Prefix length for the destination.
 */
void initialize_rtmsg(struct rtmsg *route_msg, int prefix_len);

/**
 * Add an attribute to the Netlink message.
 * @param rta Pointer to the rtattr structure.
 * @param type Attribute type.
 * @param data Attribute data.
 * @param data_len Length of the attribute data.
 */
void add_rtattr(struct rtattr **rta, int type, const void *data, int data_len);

/**
 * Process the kernel's response to a Netlink request.
 * @param sockfd File descriptor of the Netlink socket.
 * @return 0 on success, -1 on error.
 */
int process_kernel_response(int sockfd);

/**
 * Add a route to the routing table.
 * @param dest Destination address.
 * @param gateway Gateway address.
 * @param ifindex Interface index.
 * @param prefix_len Prefix length for the destination.
 * @return 0 on success, -1 on error.
 */
int add_route(struct in_addr dest, struct in_addr gateway, int ifindex, int prefix_len);

/**
 * Parse an IP/Prefix string into an in_addr structure and prefix length.
 * @param input Input string (e.g., "192.168.1.0/24").
 * @param ip Pointer to the in_addr structure.
 * @param prefix Pointer to the prefix length.
 * @return 0 on success, -1 on error.
 */
int parse_ip_and_prefix(const char *input, struct in_addr *ip, int *prefix);

#endif // ADD_ROUTE_H

