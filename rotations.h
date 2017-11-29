#pragma once
#include <stdint.h>
#include "utilities.h"

uint64_t rotate_right_around_x_axis(uint64_t o)
{
    uint64_t r = o;
    r = delta_swap(r, 32, 0xffffffff00000000);
    r = delta_swap(r, 16, 0xffff0000ffff0000);
    r = delta_swap(r, 24, 0x00ff00ff00000000);
    r = delta_swap(r, 12, 0x0f0f00000f0f0000);
    return r;
}
uint64_t rotate_left_around_x_axis(uint64_t o)
{
    uint64_t r = o;
    r = delta_swap(r, 24, 0x00ff00ff00000000);
    r = delta_swap(r, 12, 0x0f0f00000f0f0000);
    r = delta_swap(r, 32, 0xffffffff00000000);
    r = delta_swap(r, 16, 0xffff0000ffff0000);
    return r;
}
uint64_t rotate_right_around_y_axis(uint64_t o)
{
    uint64_t r = o;
    r = delta_swap(r, 32, 0xffffffff00000000);
    r = delta_swap(r, 16, 0xffff0000ffff0000);
    r = delta_swap(r, 34, 0xcccccccc00000000);
    r = delta_swap(r, 17, 0xaaaa0000aaaa0000);
    return r;
}
uint64_t rotate_left_around_y_axis(uint64_t o)
{
    uint64_t r = o;
    r = delta_swap(r, 34, 0xcccccccc00000000);
    r = delta_swap(r, 17, 0xaaaa0000aaaa0000);
    r = delta_swap(r, 32, 0xffffffff00000000);
    r = delta_swap(r, 16, 0xffff0000ffff0000);
    return r;
}
uint64_t rotate_right_around_z_axis(uint64_t o)
{
    uint64_t r = o;
    r = delta_swap(r, 8, 0xff00ff00ff00ff00);
    r = delta_swap(r, 4, 0xf0f0f0f0f0f0f0f0);
    r = delta_swap(r, 6, 0x3300330033003300);
    r = delta_swap(r, 3, 0x5050505050505050);
    return r;
}
uint64_t rotate_left_around_z_axis(uint64_t o)
{
    uint64_t r = o;
    r = delta_swap(r, 6, 0x3300330033003300);
    r = delta_swap(r, 3, 0x5050505050505050);
    r = delta_swap(r, 8, 0xff00ff00ff00ff00);
    r = delta_swap(r, 4, 0xf0f0f0f0f0f0f0f0);
    return r;
}
