#include "encoding_decoding.h"

int_least32_t encodePoint(int_least32_t x, int_least32_t y, int_least32_t width)
{
    return (y * width + x);
}

void decodePoint(int_least32_t encoded, int_least32_t width, int_least32_t* x, int_least32_t* y)
{
    *y = encoded / width;
    *x = encoded % width;
}

