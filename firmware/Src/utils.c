#include "main.h"
#include "utils.h"

// suppress bogus warning when compiling with gcc 4.3
#if (__GNUC__ >= 4 && __GNUC_MINOR__ >= 3)
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif

void hex2bin(const char* in, size_t len, uint8_t* out)
{
    static const uint8_t HEX_MAP[] = { 
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 58, 59, 60, 61, 62, 63, 64, 10, 11, 12, 13, 14, 15, 71, 72, 73, 74, 75, 76,
        77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 10, 11, 12, 13, 14, 15 
    };

    static const unsigned char* LOOKUP = HEX_MAP - 48;

    const char* end = in + len;

    while (in < end) {
        size_t xi = *(in++);
        size_t yi = *(in++);
        *(out++) = (LOOKUP[xi] << 4) | LOOKUP[yi];
    }
}