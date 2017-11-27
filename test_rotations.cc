#include <stdio.h>
#include <stdint.h>

inline constexpr uint64_t rotl(uint64_t x, int k)
{
    return (x << k) | (x >> (64-k));
}

#include "rotations.h"

uint64_t board_with_one_bit_set(int x, int y, int z)
{
    return 1uLL << (16*z + 4*y + x);
}

using ULL = unsigned long long;
static int passed, failed;
#define EXPECT(input, f, expected) \
    if (f(board_with_one_bit_set input) != board_with_one_bit_set expected) { \
        printf("FAIL: %s(%s %016llx) = %016llx when we expected %016llx\n", #f, #input, (ULL)board_with_one_bit_set input, (ULL)f(board_with_one_bit_set input), (ULL)board_with_one_bit_set expected); \
        failed += 1; \
    } else { \
        passed += 1; \
    }

int main()
{
    EXPECT((0,0,0), rotate_right_around_x_axis, (0,3,0));
    EXPECT((1,0,0), rotate_right_around_x_axis, (1,3,0));
    EXPECT((2,1,1), rotate_right_around_x_axis, (2,2,1));
    EXPECT((2,2,1), rotate_right_around_x_axis, (2,2,2));
    EXPECT((0,3,0), rotate_right_around_x_axis, (0,3,3));

    EXPECT((0,3,0), rotate_left_around_x_axis, (0,0,0));
    EXPECT((1,3,0), rotate_left_around_x_axis, (1,0,0));
    EXPECT((2,2,1), rotate_left_around_x_axis, (2,1,1));
    EXPECT((2,2,2), rotate_left_around_x_axis, (2,2,1));
    EXPECT((0,3,3), rotate_left_around_x_axis, (0,3,0));

    EXPECT((0,0,0), rotate_right_around_y_axis, (0,0,3));
    EXPECT((1,0,0), rotate_right_around_y_axis, (0,0,2));
    EXPECT((2,1,1), rotate_right_around_y_axis, (1,1,1));
    EXPECT((2,2,1), rotate_right_around_y_axis, (1,2,1));
    EXPECT((0,3,0), rotate_right_around_y_axis, (0,3,3));

    EXPECT((0,0,0), rotate_right_around_z_axis, (3,0,0));
    EXPECT((1,0,0), rotate_right_around_z_axis, (3,1,0));
    EXPECT((2,1,1), rotate_right_around_z_axis, (2,2,1));
    EXPECT((2,2,1), rotate_right_around_z_axis, (1,2,1));
    EXPECT((0,3,0), rotate_right_around_z_axis, (0,0,0));

    printf("All tests finished. %d passed, %d failed.\n", passed, failed);
}
