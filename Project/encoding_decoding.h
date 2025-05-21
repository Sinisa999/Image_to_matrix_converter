#ifndef ENCODING_DECODING_H
#define ENCODING_DECODING_H

#include<stdlib.h>
#include<stdint.h>

int_least32_t encodePoint(int_least32_t x, int_least32_t y, int_least32_t width);


void decodePoint(int_least32_t encoded, int_least32_t width, int_least32_t* x, int_least32_t* y);


#endif
