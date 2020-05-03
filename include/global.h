#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include <string.h>
#include <stdint.h>

#include "gba/gba.h"
#include "constants/global.h"

// Prevent cross-jump optimization.
#define BLOCK_CROSS_JUMP asm("");

// to help in decompiling
#define asm_comment(x) asm volatile("@ -- " x " -- ")
#define asm_unified(x) asm(".syntax unified\n" x "\n.syntax divided")

///
/// useful general macros
///

#define ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))

#define TEMP_SWAP(a, b, temp) \
{                             \
    temp = a;                 \
    a = b;                    \
    b = temp;                 \
}

#define XOR_SWAP(a, b) \
{                      \
    a ^= b;            \
    b ^= a;            \
    a ^= b;            \
}

///
/// useful math macros
///

// Converts a number to Q8.8 fixed-point format
#define Q_8_8(n) ((s16)((n) * 256))

// Converts a number to Q4.12 fixed-point format
#define Q_4_12(n)  ((int16_t)((n) * 4096))

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) >= (b) ? (a) : (b))

#define abs(x) (((x) < 0) ? -(x) : (x))

#endif // GUARD_GLOBAL_H
