#ifndef BMP_H_
#define BMP_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct tagBITMAPFILEHEADER
{
    uint_least16_t bfType;    /*specificira tip fajla*/
    uint_least32_t bfSize;    /*specificira velicinu u bajtovima bitmap fajla*/
    uint_least16_t bfReserved1;   /*rezervisano, mora biti 0*/
    uint_least16_t bfReserved2;   /*rezervisano, mora biti 0*/
    uint_least32_t bfOffBits;     /*specificira offset u bajtima od bitmapfileheader-a do bitmap bita*/
} __attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    uint_least32_t biSize;    /*specifira broj bajtova koje struktura zahteva*/
    int_least32_t biWidth;  /*specificira sirinu u pikselima*/
    int_least32_t biHeight; /*specificira visinu u pikselima*/
    uint_least16_t biPlanes;    /*specificira broj komponenti boja, mora biti 1*/
    uint_least16_t biBitCount;  /*specificira broj bitova po pikselu (1 u ovom slucaju)*/
    uint_least32_t biCompression;   /*specificira vrstu kompresije*/
    uint_least32_t biSizeImage;     /*velicina slike u bajtima*/
    int_least32_t biXPelsPerMeter;  /*broj piksela po x osi*/
    int_least32_t biYPelsPerMeter;  /*broj piksela po y osi*/
    uint_least32_t biClrUsed;       /*broj boja koje bitmapa koristi*/
    uint_least32_t biClrImportant;  /*broj boja koje su vazne*/
} __attribute__((packed)) BITMAPINFOHEADER;

uint_least8_t* LoadBitmapFile(char* filename, BITMAPFILEHEADER* bitmapFileHeader, BITMAPINFOHEADER* bitmapInfoHeader);




#endif
