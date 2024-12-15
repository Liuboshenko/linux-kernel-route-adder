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

## Usage
Run the utility with superuser privileges:
```bash
sudo ./add_route <DEST_IP/Prefix> <GATEWAY_IP> <INTERFACE>
```

For more details, see the [Usage Guide](./docs/USAGE.md).

### Examples

#### Add a route to a subnet:
```bash
sudo ./add_route 192.168.128.0/24 192.168.100.1 eth0
```

#### Add a route to a single IP address:
```bash
sudo ./add_route 192.168.128.128/32 192.168.100.1 eth0
```

### Explanation of Parameters
- `<DEST_IP/Prefix>`: The destination network or IP address with the prefix length (e.g., `192.168.128.0/24` for a subnet, `192.168.128.128/32` for a single address).
- `<GATEWAY_IP>`: The gateway IP address through which the route is accessible.
- `<INTERFACE>`: The name of the network interface (e.g., `eth0`, `wlan0`).

## Documentation
- [Usage Guide](./docs/USAGE.md): Detailed instructions and advanced examples.
- [Contributing Guide](./docs/CONTRIBUTING.md): Guidelines for contributing to this project.
- [Design Document](./docs/DESIGN.md): Technical details and design decisions.

## Error Handling
- The program validates the input parameters and ensures compatibility with the kernel routing table.
- If the route cannot be added, an error message will specify the cause (e.g., "Invalid argument").

## Contribution
Contributions are welcome! Feel free to open issues or submit pull requests.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

