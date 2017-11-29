#!/usr/bin/env python

def board_with_one_bit_set(x, y, z):
    return 1 << (16*z + 4*y + x)

def to_hex(mask):
    return "0x%04X'%04X'%04X'%04X" % (
        ((mask >> 48) & 0xFFFF),
        ((mask >> 32) & 0xFFFF),
        ((mask >> 16) & 0xFFFF),
        ((mask >> 0) & 0xFFFF),
    )

def rotl_function_defn(function_name, original, rotated):
    bits_by_rotation = {}
    for b in xrange(64):
        o = original.index(b)
        r = rotated.index(b)
        rotl_amount = ((r - o) + 64) % 64
        bits_by_rotation.setdefault(rotl_amount, []).append(r)
    defn = 'uint64_t %s(uint64_t o)\n' % function_name
    defn += '{\n'
    defn += '    uint64_t r = 0;\n'
    for amount, bits in sorted(bits_by_rotation.iteritems()):
        mask = sum(1 << b for b in bits)
        defn += '    r |= rotl(o, %d) & %s;\n' % (amount, to_hex(mask))
    defn += '    return r;\n'
    defn += '}'
    return defn

original = [
    63, 62, 61, 60,
    59, 58, 57, 56,  # rear
    55, 54, 53, 52,  # face
    51, 50, 49, 48,
                   47, 46, 45, 44,
                   43, 42, 41, 40,
                   39, 38, 37, 36,
                   35, 34, 33, 32,
                                  31, 30, 29, 28,
                                  27, 26, 25, 24,
                                  23, 22, 21, 20,
                                  19, 18, 17, 16,
                                                 15, 14, 13, 12,
                                                 11, 10, 9,  8,    # front
                                                 7,  6,  5,  4,    # face
                                                 3,  2,  1,  0,
]

rotated_around_x_axis = [
    15, 14, 13, 12,
    31, 30, 29, 28,
    47, 46, 45, 44,
    63, 62, 61, 60,
                   11, 10, 9,  8,
                   27, 26, 25, 24,
                   43, 42, 41, 40,
                   59, 58, 57, 56,
                                  7,  6,  5,  4,
                                  23, 22, 21, 20,
                                  39, 38, 37, 36,
                                  55, 54, 53, 52,
                                                 3,  2,  1,  0,
                                                 19, 18, 17, 16,
                                                 35, 34, 33, 32,
                                                 51, 50, 49, 48,
]

rotated_around_y_axis = [
    60, 44, 28, 12,
    56, 40, 24, 8,
    52, 36, 20, 4,
    48, 32, 16, 0,
                   61, 45, 29, 13,
                   57, 41, 25, 9,
                   53, 37, 21, 5,
                   49, 33, 17, 1,
                                  62, 46, 30, 14,
                                  58, 42, 26, 10,
                                  54, 38, 22, 6,
                                  50, 34, 18, 2,
                                                 63, 47, 31, 15,
                                                 59, 43, 27, 11,
                                                 55, 39, 23, 7,
                                                 51, 35, 19, 3,
]

rotated_around_z_axis = [
    51, 55, 59, 63,
    50, 54, 58, 62,
    49, 53, 57, 61,
    48, 52, 56, 60,
                   35, 39, 43, 47,
                   34, 38, 42, 46,
                   33, 37, 41, 45,
                   32, 36, 40, 44,
                                  19, 23, 27, 31,
                                  18, 22, 26, 30,
                                  17, 21, 25, 29,
                                  16, 20, 24, 28,
                                                 3,  7,  11, 15,
                                                 2,  6,  10, 14,
                                                 1,  5,  9,  13,
                                                 0,  4,  8,  12,
]

print '#pragma once'
print '#include <stdint.h>'
print '#include "utilities.h"'
print ''
print rotl_function_defn('rotate_right_around_x_axis', original, rotated_around_x_axis)
print rotl_function_defn('rotate_left_around_x_axis', rotated_around_x_axis, original)
print rotl_function_defn('rotate_right_around_y_axis', original, rotated_around_y_axis)
print rotl_function_defn('rotate_left_around_y_axis', rotated_around_y_axis, original)
print rotl_function_defn('rotate_right_around_z_axis', original, rotated_around_z_axis)
print rotl_function_defn('rotate_left_around_z_axis', rotated_around_z_axis, original)
