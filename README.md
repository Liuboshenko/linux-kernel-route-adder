# linux-kernel-route-adder
A C utility to add static routes to the Linux kernel's Forwarding Information Base (FIB) using the Netlink protocol.

# Linux FIB Route Adder

A lightweight C-based utility to add static routes to the Linux kernel's Forwarding Information Base (FIB) using the Netlink protocol.

## Features
- Supports adding routes to both subnets and individual IP addresses.
- Communicates directly with the kernel's FIB via Netlink.
- Robust error handling and input validation.

## Requirements
- Linux-based operating system.
- GCC or a compatible C compiler.

## How to Build
Clone the repository and compile the source code:
```bash
git clone https://github.com/Liuboshenko/linux-kernel-route-adder.git
cd linux-fib-route-adder
make

# OR
git clone https://github.com/Liuboshenko/linux-kernel-route-adder.git
cd linux-fib-route-adder/src
gcc -o add_route main.c add_route.c -Wall
```