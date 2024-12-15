# Design Document: Linux FIB Route Adder

This document outlines the design and architecture of the Linux FIB Route Adder project.

## Overview
The Linux FIB Route Adder is a C-based utility that interacts with the Linux kernel's Forwarding Information Base (FIB) using the Netlink protocol. It facilitates adding static routes for subnets and individual IP addresses with robust error handling and input validation.

## Key Components

### 1. **Netlink Communication**
- The utility uses a Netlink socket to communicate with the Linux kernel.
- The `RTM_NEWROUTE` message type is used to add new routes to the FIB.
- Attributes like destination (`RTA_DST`), gateway (`RTA_GATEWAY`), and interface (`RTA_OIF`) are included in the message.

### 2. **Input Validation**
- The utility validates the format of IP addresses and ensures compatibility between the destination address and prefix length.
- Example: For a `/24` prefix, the destination must align with the subnet boundary.

### 3. **Error Handling**
- The utility processes kernel responses to detect and report errors, such as invalid arguments or unreachable gateways.
- Specific error codes are translated into user-friendly messages.

### 4. **Modular Design**
- The project is divided into:
  - **`add_route.c`**: Implements core Netlink communication and route addition logic.
  - **`main.c`**: Handles user input and orchestrates the execution.
  - **`add_route.h`**: Declares shared functions and structures.

## Workflow
1. **Input Parsing**: The utility parses user input (destination, gateway, and interface).
2. **Netlink Message Construction**:
   - Initializes the Netlink socket and message header.
   - Adds required attributes to the message.
3. **Message Sending**: Sends the constructed message to the kernel.
4. **Kernel Response Handling**:
   - Processes the response to confirm success or detect errors.
   - Displays meaningful output to the user.

## Key Design Decisions
- **Netlink Protocol**: Direct communication with the kernel ensures lightweight and fast operations.
- **Input Validation**: Prevents invalid route entries by checking the compatibility of inputs.
- **Error Reporting**: Translates low-level Netlink error codes into understandable messages.

## Limitations
- Currently supports only IPv4 routes.
- Requires superuser privileges to execute.

## Future Enhancements
- Add support for IPv6 routes.
- Include route deletion functionality.
- Extend compatibility for advanced Netlink attributes, such as metrics and multipath routes.

