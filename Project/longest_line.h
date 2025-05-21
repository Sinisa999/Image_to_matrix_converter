#ifndef LONGEST_LINE_H
#define LONGEST_LINE_H

#include "stacklib.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>




int_least32_t dfs(uint_least8_t* image, int_least32_t width, int_least32_t height, int_least32_t startX, int_least32_t startY, uint_least8_t* visited);

int_least32_t findLongestLine(uint_least8_t* image, int_least32_t width, int_least32_t height);

#endif
