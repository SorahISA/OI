#!/usr/bin/env python3


def decompress(strings):
    ctx_bytes = bytearray([int(strings[i:i+2], 16)
                          for i in range(0, len(strings), 2)])
    fsize, *codes = ctx_bytes
    freq_codes, (padding, *codes) = codes[:fsize], codes[fsize:]

    iter_freq = zip(freq_codes[::3], freq_codes[1::3], freq_codes[2::3])
    tables = dict(('{:0{len}b}'.format(bcode, len=code_len), chr(bchr))
                  for bchr, bcode, code_len in iter_freq)

    code_bits = "".join('{:08b}'.format(c) for c in codes)
    bits = decoded_ctx = ""
    for bit in code_bits[:padding * -1]:
        bits += bit
        if bits in tables:
            decoded_ctx += tables.get(bits)
            bits = ""

    return decoded_ctx


if __name__ == '__main__':
    line = input()
    print(decompress(line).strip())
