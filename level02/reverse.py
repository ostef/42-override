#!/usr/bin/env python3
import argparse

def reverse_endian_64(hexstr):
    """Reverse endianness of a 64-bit hex string"""
    hexstr = hexstr.lower().replace("0x", "").zfill(16)
    bytes_list = [hexstr[i:i+2] for i in range(0, 16, 2)]
    return "".join(bytes_list[::-1])

def hex_to_ascii(hexstr):
    """Convert hex (exact bytes) to ASCII without modification"""
    return bytes.fromhex(hexstr).decode("latin-1")

def main():
    parser = argparse.ArgumentParser(description="Fix endian + extract ascii")
    parser.add_argument("--addresses", help="addresses", required=True)
    args = parser.parse_args()

    addresses = args.addresses.split()
    output = []

    for addr in addresses:
        if addr == "(nil)" or addr == "0x0":
            continue 

        if addr.startswith("0x"):
            rev = reverse_endian_64(addr)
            ascii_value = hex_to_ascii(rev)
            output.append(ascii_value)

    print("".join(output))

if __name__ == "__main__":
    main()
