#include "bmp.h"

uint_least8_t* LoadBitmapFile(char* filename, BITMAPFILEHEADER* bitmapFileHeader, BITMAPINFOHEADER* bitmapInfoHeader)
{
    FILE* filePtr;
    uint_least8_t* bitmapImage;
    int_least32_t imageIdx;
    int_least32_t byteIdx;
    uint_least8_t byte;

    /*otvaramo datoteku u rezimu binarnog citanja*/
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
    {
        return NULL;
    }

    /*cita se zaglavlje bitmap datoteke*/
    fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    /*proveravamo da li je datoteka monohromna (1-bit BMP datoteka)*/
    if (bitmapFileHeader->bfType != 0x4D42)
    {
        printf("Error: Datoteka nije u BMP formatu!.\n");
        fclose(filePtr);
        return NULL;
    }

    /*citanje nitmap info headera*/
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

    /*pozicioniranje pokazivaca na pocetak bitmap datoteke*/
    fseek(filePtr, bitmapFileHeader->bfOffBits, SEEK_SET);

    /*alociranje memorije za niz u koji ce biti smesteni podaci iz bitmap datoteke*/
    bitmapImage = (uint_least8_t*)malloc(bitmapInfoHeader->biSizeImage);

    /*provera da li je zauzimanje memorije uspesno izvrseno*/
    if (!bitmapImage)
    {
        fclose(filePtr);
        return NULL;
    }

    /*citanje podataka iz bitmap datoteke*/
    fread(bitmapImage, bitmapInfoHeader->biSizeImage, 1, filePtr);

    /*Alokacija memorije za binarnu sliku (1-bit po pikselu)*/
    uint_least8_t* binaryImage = (uint_least8_t*)malloc(bitmapInfoHeader->biWidth * abs(bitmapInfoHeader->biHeight));

    if (!binaryImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    /* Poravnanje reda */
    int_least32_t paddedRowSize = ((bitmapInfoHeader->biWidth + 31) / 32) * 4;

    /* racunanje velicine ukoliko nije u header-u */
    if (bitmapInfoHeader->biSizeImage == 0) {
        bitmapInfoHeader->biSizeImage = paddedRowSize * abs(bitmapInfoHeader->biHeight);
    }


    printf("Bit Count: %d\n", bitmapInfoHeader->biBitCount);
    printf("Binary Image Size: %d bytes\n", (bitmapInfoHeader->biWidth * abs(bitmapInfoHeader->biHeight) + 7) / 8);
    printf("Bitmap Width: %d, Height: %d\n", bitmapInfoHeader->biWidth, abs(bitmapInfoHeader->biHeight));
    printf("Padded Row Size: %d\n", paddedRowSize);
    printf("Allocated Bitmap Size: %d bytes\n", bitmapInfoHeader->biSizeImage);

    /*Konvertovanje slike u format matrice 0 i 1*/
    for (imageIdx = 0; imageIdx < abs(bitmapInfoHeader->biHeight); ++imageIdx)
    {
        for (byteIdx = 0; byteIdx < paddedRowSize; ++byteIdx)
        {
            byte = bitmapImage[imageIdx * paddedRowSize + byteIdx];
            for (int_least32_t bit = 0; bit < 8 && (byteIdx * 8 + bit) < bitmapInfoHeader->biWidth; ++bit)
            {
                int_least32_t pixelIndex = imageIdx * bitmapInfoHeader->biWidth + (byteIdx * 8 + bit);
                binaryImage[pixelIndex] = (byte & (1 << (7 - bit))) ? 0 : 1;
            }
        }
    }

    free(bitmapImage);
    fclose(filePtr);
    return binaryImage;

}
