# Usage Guide for Linux FIB Route Adder

This guide provides detailed instructions and advanced examples for using the Linux FIB Route Adder.

## Adding a Route to a Subnet
Example:
```bash
sudo ./add_route 192.168.128.0/24 192.168.100.1 eth0
```

## Adding a Route to a Single IP Address
Example:
```bash
sudo ./add_route 192.168.128.128/32 192.168.100.1 eth0
```
## Handling Errors
- **Invalid Argument (Code 22):** Ensure that the destination matches the prefix length. Use `/32` for single IP routes.
- **No Such Device:** Check that the interface name is correct.

## FAQ
### Why is my route not added?
Ensure the gateway is reachable and the destination address matches the prefix length.
