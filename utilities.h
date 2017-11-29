#pragma once

inline constexpr uint64_t rotl(uint64_t x, int k)
{
    return (x << k) | (x >> (64-k));
}

inline constexpr uint64_t delta_swap(uint64_t a, int delta, uint64_t mask)
{
    uint64_t b = (a ^ (a << delta)) & mask;
    return a ^ b ^ (b >> delta);
}
