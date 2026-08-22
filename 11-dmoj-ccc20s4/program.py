# To prevent TLE, stack-allocated variables are used rather than putting them into lists or matrices.

# Here, `order` is the string containing the letters which we from here on refer to as
# the 1st, 2nd, and 3rd letters. This allows for accommodating an 'ABC' target or an 'ACB' target configuration.
def get_min_swaps(s, order):
    # Variables containing the counts of the 1st, 2nd, and 3rd letters.
    c1, c2, c3 = [s.count(letter) for letter in order]
    # We extract out the letters in the `order` argument as well.
    l1, l2, l3 = order

    # The variables named in the format `dij` refer to the number of instances where
    # the `i`-th letter should appear in the target configuration but the `j`-th letter appears in the actual string.
    d12 = s[:c1].count(l2)
    d13 = s[:c1].count(l3)
    d21 = s[c1 : c1 + c2].count(l1)
    d23 = s[c1 : c1 + c2].count(l3)
    d31 = s[c1 + c2 : c1 + c2 + c3].count(l1)
    d32 = s[c1 + c2 : c1 + c2 + c3].count(l2)

    n = len(s)
    # The string has maximum length `10^6`,
    # so this is a reasonable upper bound for number of swaps ever possibly needed.
    min_swaps = 2 * 10 ** 6

    # We test all `n` possible rotations of the target configuration,
    # starting with the `l1 * c1 + l2 * c2 + l3 * c3` configuration.
    for i in range(n):
        # Some mismatch configurations can be cancelled by directly swapping two out-of-place letters.
        swap2 = min(d12, d21) + min(d13, d31) + min(d23, d32)
        # The remaining mismatches can only be corrected by conducting two swaps to permute three incorrect letters.
        swap3 = max(d12, d21) - min(d12, d21)
        total_swaps = swap2 + 2 * swap3

        min_swaps = min(min_swaps, total_swaps)

        # When we move to the next rotation,
        # we keep track of which character is no longer overlapping with each contiguous stretch of the target configuration.
        leaving1 = s[i % n]
        leaving2 = s[(c1 + i) % n]
        leaving3 = s[(c1 + c2 + i) % n]

        # We also keep track of which character is newly overlapping with each stretch.
        entering1 = s[(c1 + i) % n]
        entering2 = s[(c1 + c2 + i) % n]
        entering3 = s[(c1 + c2 + c3 + i) % n]

        # We decrement the difference/mismatch variables according to which type of letter is no longer being counted for each target letter.
        d12, d13 = (d12 - 1, d13) if leaving1 == l2 else (d12, d13 - 1) if leaving1 == l3 else (d12, d13)
        d21, d23 = (d21 - 1, d23) if leaving2 == l1 else (d21, d23 - 1) if leaving2 == l3 else (d21, d23)
        d31, d32 = (d31 - 1, d32) if leaving3 == l1 else (d31, d32 - 1) if leaving3 == l2 else (d31, d32)

        # We increment the difference/mismatch variables according to which type of letter is newly being counted for each target letter.
        d12, d13 = (d12 + 1, d13) if entering1 == l2 else (d12, d13 + 1) if entering1 == l3 else (d12, d13)
        d21, d23 = (d21 + 1, d23) if entering2 == l1 else (d21, d23 + 1) if entering2 == l3 else (d21, d23)
        d31, d32 = (d31 + 1, d32) if entering3 == l1 else (d31, d32 + 1) if entering3 == l2 else (d31, d32)

    return min_swaps

s = input()
# We test two possible configurations: "ABC" or "ACB".
# All other configurations (like "BAC" or "CBA") are just rotations of these two.
swaps1 = get_min_swaps(s, 'ABC')
swaps2 = get_min_swaps(s, 'ACB')
print(min(swaps1, swaps2))
