#pragma once

inline constexpr uint64_t board_with_one_bit_set(int x, int y, int z)
{
    return 1uLL << (16*z + 4*y + x);
}

inline constexpr uint64_t rotl(uint64_t x, int k)
{
    return (x << k) | (x >> (64-k));
}

inline constexpr uint64_t delta_swap(uint64_t a, int delta, uint64_t mask)
{
    if (((mask >> delta) ^ mask) == 0xFFFF'FFFF'FFFF'FFFF) {
        // Neither Clang nor GCC can figure out that this rewrite is safe,
        // but both are capable of evaluating the above expression at
        // compile time. So we're just helping them out here.
        return ((a << delta) & mask) | ((a & mask) >> delta);
    } else {
        uint64_t b = (a ^ (a << delta)) & mask;
        return a ^ b ^ (b >> delta);
    }
}
