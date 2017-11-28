#pragma once
#include <stdint.h>

uint64_t rotate_right_around_x_axis(uint64_t o)
{
    uint64_t r = 0;
    r |= rotl(o, 4) & 0x0000'0000'0F00'0000;
    r |= rotl(o, 8) & 0x00F0'0000'0000'0000;
    r |= rotl(o, 12) & 0x0000'0000'0000'F000;
    r |= rotl(o, 16) & 0x0000'0F00'0000'000F;
    r |= rotl(o, 24) & 0x0000'0000'F000'0000;
    r |= rotl(o, 28) & 0x0F00'0000'000F'0000;
    r |= rotl(o, 36) & 0x0000'F000'0000'00F0;
    r |= rotl(o, 40) & 0x0000'000F'0000'0000;
    r |= rotl(o, 48) & 0xF000'0000'00F0'0000;
    r |= rotl(o, 52) & 0x000F'0000'0000'0000;
    r |= rotl(o, 56) & 0x0000'0000'0000'0F00;
    r |= rotl(o, 60) & 0x0000'00F0'0000'0000;
    return r;
}
uint64_t rotate_left_around_x_axis(uint64_t o)
{
    uint64_t r = 0;
    r |= rotl(o, 4) & 0x0000'0F00'0000'0000;
    r |= rotl(o, 8) & 0x0000'0000'000F'0000;
    r |= rotl(o, 12) & 0xF000'0000'0000'0000;
    r |= rotl(o, 16) & 0x0000'00F0'0000'F000;
    r |= rotl(o, 24) & 0x0F00'0000'0000'0000;
    r |= rotl(o, 28) & 0x0000'000F'0000'0F00;
    r |= rotl(o, 36) & 0x00F0'0000'F000'0000;
    r |= rotl(o, 40) & 0x0000'0000'0000'00F0;
    r |= rotl(o, 48) & 0x000F'0000'0F00'0000;
    r |= rotl(o, 52) & 0x0000'0000'0000'000F;
    r |= rotl(o, 56) & 0x0000'F000'0000'0000;
    r |= rotl(o, 60) & 0x0000'0000'00F0'0000;
    return r;
}
uint64_t rotate_right_around_y_axis(uint64_t o)
{
    uint64_t r = 0;
    r |= rotl(o, 1) & 0x0000'4444'0000'0000;
    r |= rotl(o, 3) & 0x8888'0000'0000'0000;
    r |= rotl(o, 14) & 0x0000'0000'1111'0000;
    r |= rotl(o, 16) & 0x0000'2222'0000'8888;
    r |= rotl(o, 18) & 0x4444'0000'0000'0000;
    r |= rotl(o, 31) & 0x0000'1111'0000'4444;
    r |= rotl(o, 33) & 0x2222'0000'8888'0000;
    r |= rotl(o, 46) & 0x0000'0000'0000'2222;
    r |= rotl(o, 48) & 0x1111'0000'4444'0000;
    r |= rotl(o, 50) & 0x0000'8888'0000'0000;
    r |= rotl(o, 61) & 0x0000'0000'0000'1111;
    r |= rotl(o, 63) & 0x0000'0000'2222'0000;
    return r;
}
uint64_t rotate_left_around_y_axis(uint64_t o)
{
    uint64_t r = 0;
    r |= rotl(o, 1) & 0x0000'0000'4444'0000;
    r |= rotl(o, 3) & 0x0000'0000'0000'8888;
    r |= rotl(o, 14) & 0x2222'0000'0000'0000;
    r |= rotl(o, 16) & 0x0000'4444'0000'1111;
    r |= rotl(o, 18) & 0x0000'0000'8888'0000;
    r |= rotl(o, 31) & 0x4444'0000'1111'0000;
    r |= rotl(o, 33) & 0x0000'8888'0000'2222;
    r |= rotl(o, 46) & 0x0000'1111'0000'0000;
    r |= rotl(o, 48) & 0x8888'0000'2222'0000;
    r |= rotl(o, 50) & 0x0000'0000'0000'4444;
    r |= rotl(o, 61) & 0x1111'0000'0000'0000;
    r |= rotl(o, 63) & 0x0000'2222'0000'0000;
    return r;
}
uint64_t rotate_right_around_z_axis(uint64_t o)
{
    uint64_t r = 0;
    r |= rotl(o, 1) & 0x0040'0040'0040'0040;
    r |= rotl(o, 2) & 0x2000'2000'2000'2000;
    r |= rotl(o, 3) & 0x0008'0008'0008'0008;
    r |= rotl(o, 4) & 0x0400'0400'0400'0400;
    r |= rotl(o, 6) & 0x0080'0080'0080'0080;
    r |= rotl(o, 7) & 0x4000'4000'4000'4000;
    r |= rotl(o, 9) & 0x0800'0800'0800'0800;
    r |= rotl(o, 12) & 0x8000'8000'8000'8000;
    r |= rotl(o, 52) & 0x0001'0001'0001'0001;
    r |= rotl(o, 55) & 0x0010'0010'0010'0010;
    r |= rotl(o, 57) & 0x0002'0002'0002'0002;
    r |= rotl(o, 58) & 0x0100'0100'0100'0100;
    r |= rotl(o, 60) & 0x0020'0020'0020'0020;
    r |= rotl(o, 61) & 0x1000'1000'1000'1000;
    r |= rotl(o, 62) & 0x0004'0004'0004'0004;
    r |= rotl(o, 63) & 0x0200'0200'0200'0200;
    return r;
}
uint64_t rotate_left_around_z_axis(uint64_t o)
{
    uint64_t r = 0;
    r |= rotl(o, 1) & 0x0400'0400'0400'0400;
    r |= rotl(o, 2) & 0x0010'0010'0010'0010;
    r |= rotl(o, 3) & 0x8000'8000'8000'8000;
    r |= rotl(o, 4) & 0x0200'0200'0200'0200;
    r |= rotl(o, 6) & 0x4000'4000'4000'4000;
    r |= rotl(o, 7) & 0x0100'0100'0100'0100;
    r |= rotl(o, 9) & 0x2000'2000'2000'2000;
    r |= rotl(o, 12) & 0x1000'1000'1000'1000;
    r |= rotl(o, 52) & 0x0008'0008'0008'0008;
    r |= rotl(o, 55) & 0x0004'0004'0004'0004;
    r |= rotl(o, 57) & 0x0080'0080'0080'0080;
    r |= rotl(o, 58) & 0x0002'0002'0002'0002;
    r |= rotl(o, 60) & 0x0040'0040'0040'0040;
    r |= rotl(o, 61) & 0x0001'0001'0001'0001;
    r |= rotl(o, 62) & 0x0800'0800'0800'0800;
    r |= rotl(o, 63) & 0x0020'0020'0020'0020;
    return r;
}
