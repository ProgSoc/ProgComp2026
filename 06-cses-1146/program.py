n = int(input())
# This formula is derived by considering some position `d` bits away from the least significant bit of `n`.
# The pattern at this position is a block of `2^d` 1-bits followed by `2^d` 0-bits.
# Interpreting the bitmask of the bits to the left (more significant) as a binary integer
# tells you how many 1-bit blocks (of size `2^d`) you have passed through already.
# Interpreting the bitmask of the bits to the right (less signficant) as a binary integer
# tells you how many 1-bits you have previously seen if you are currently within a 1-bit block.
print(sum(((n >> (d+1)) << d) + ((n >> d) & 1) * (1 + (n & ((1 << d) - 1))) for d in range(n.bit_length())))
