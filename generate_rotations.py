#!/usr/bin/env python

import argparse

def board_with_one_bit_set(x, y, z):
    return 1 << (16*z + 4*y + x)

def coords_from_board(bb):
    for x in range(4):
        for y in range(4):
            for z in range(4):
                if board_with_one_bit_set(x, y, z) == bb:
                    return (x, y, z)
    assert False

def permute_bits(bb, original, rotated):
    result = 0
    for i in xrange(64):
        o = 63 - original[i]
        r = rotated.index(original[i])
        if (bb & (1 << i)):
            result |= (1 << r)
    return result

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

def test_function_defn(function_name, original, rotated):
    defn = 'void test_%s()\n' % function_name
    defn += '{\n'
    for x in range(4):
        for y in range(4):
            for z in range(4):
                inbb = board_with_one_bit_set(x, y, z)
                outbb = permute_bits(inbb, original, rotated)
                ex, ey, ez = coords_from_board(outbb)
                defn += '    EXPECT1((%d,%d,%d), %s, (%d,%d,%d))\n' % (
                    x, y, z, function_name, ex, ey, ez,
                )
    for inbb in [0xA5A55A5AA5A55A5A, 0xCC33CC3333CC33CC, 0x123456789ABCDEF, 0x38D53645E690546D]:
        outbb = permute_bits(inbb, original, rotated)
        defn += '    EXPECTb(0x%016X, %s, 0x%016X)\n' % (
            inbb, function_name, outbb,
        )
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

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--rotl', action='store_true', help='Generate rotl-based "rotations.h" and dump to stdout')
    parser.add_argument('--tests', action='store_true', help='Generate "test_rotations.cc" and dump to stdout')
    options = parser.parse_args()

    if options.rotl:
        print '#pragma once'
        print '#include <stdint.h>'
        print '#include "utilities.h"\n'
        print rotl_function_defn('rotate_right_around_x_axis', original, rotated_around_x_axis) + '\n'
        print rotl_function_defn('rotate_left_around_x_axis', rotated_around_x_axis, original) + '\n'
        print rotl_function_defn('rotate_right_around_y_axis', original, rotated_around_y_axis) + '\n'
        print rotl_function_defn('rotate_left_around_y_axis', rotated_around_y_axis, original) + '\n'
        print rotl_function_defn('rotate_right_around_z_axis', original, rotated_around_z_axis) + '\n'
        print rotl_function_defn('rotate_left_around_z_axis', rotated_around_z_axis, original) + '\n'

    if options.tests:
        print r"""
#include <stdio.h>
#include <stdint.h>

#include "rotations.h"
#include "utilities.h"

static int passed, failed;
#define EXPECT1(input, f, expected) \
    if (f(board_with_one_bit_set input) != board_with_one_bit_set expected) { \
        printf("FAIL: %s(%s %016llx) = %016llx when we expected %016llx\n", \
            #f, #input, (unsigned long long)board_with_one_bit_set input, \
            (unsigned long long)f(board_with_one_bit_set input), \
            (unsigned long long)board_with_one_bit_set expected); \
        failed += 1; \
    } else { \
        passed += 1; \
    }

#define EXPECTb(input, f, expected) \
    if (f(input) != expected) { \
        printf("FAIL: %s(%016llx) = %016llx when we expected %016llx\n", \
            #f, (unsigned long long)input, \
            (unsigned long long)f(input), \
            (unsigned long long)expected); \
        failed += 1; \
    } else { \
        passed += 1; \
    }

"""
        print test_function_defn('rotate_right_around_x_axis', original, rotated_around_x_axis) + '\n'
        print test_function_defn('rotate_left_around_x_axis', rotated_around_x_axis, original) + '\n'
        print test_function_defn('rotate_right_around_y_axis', original, rotated_around_y_axis) + '\n'
        print test_function_defn('rotate_left_around_y_axis', rotated_around_y_axis, original) + '\n'
        print test_function_defn('rotate_right_around_z_axis', original, rotated_around_z_axis) + '\n'
        print test_function_defn('rotate_left_around_z_axis', rotated_around_z_axis, original) + '\n'
        print 'int main()'
        print '{'
        print '    test_rotate_right_around_x_axis();'
        print '    test_rotate_left_around_x_axis();'
        print '    test_rotate_right_around_y_axis();'
        print '    test_rotate_left_around_y_axis();'
        print '    test_rotate_right_around_z_axis();'
        print '    test_rotate_left_around_z_axis();'
        print r'    printf("All tests finished. %d passed, %d failed.\n", passed, failed);'
        print '}'
