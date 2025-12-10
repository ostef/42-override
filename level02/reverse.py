#!/usr/bin/env python3
import argparse

def reverse_endian_64(hexstr):
    """Reverse endianness of a 64-bit hex string"""
    hexstr = hexstr.lower().replace("0x", "").zfill(16)
    bytes_list = [hexstr[i:i+2] for i in range(0, 16, 2)]
    return "".join(bytes_list[::-1])

def hex_to_ascii_safe(hexstr):
    """Convert hex to ASCII printable, replace non-printable with '.'"""
    b = bytes.fromhex(hexstr)
    return "".join(chr(c) if 32 <= c <= 126 else '.' for c in b)

def main():
    parser = argparse.ArgumentParser(description="Reverse addresses + hex to ASCII")
    parser.add_argument("--addresses", help="addresses", required=True)
    args = parser.parse_args()

    addresses = args.addresses.split()
    output = []

    for addr in reversed(addresses):
        if addr == "(nil)":
            rev = "0" * 16
        else:
            rev = reverse_endian_64(addr)

        ascii_value = hex_to_ascii_safe(rev)
        output.append(ascii_value)

    print("".join(output))

if __name__ == "__main__":
    main()
