/*
Sinisa Ilic RA153/2021

------------------------------------------------------------------------------------------------------------------------------------------

Zadatak 43: Napraviti modul koji predstavlja stek. Modul izvesti kao staticku biblioteku.
Napisati program koji ucitava sliku iz datoteke u formi matrice nula i jedinica. Zatim realizovati modul koji
pronalazi najduzu liniju u slici i vraca njenu duzinu u pikselima. Uzeti u obzir da je na pretpostavaljenom
namenskom procesoru maksimalna dubina poziva funkcija 4.

------------------------------------------------------------------------------------------------------------------------------------------


Resenje: Program se sastoji iz 5 .c datoteka: main.c, stacklib.c, bmp.c, encoding_decoding.c i longest_line.c
i 4 .h datoteka: stacklib.h, bmp.h, encoding_decoding.h i longest_line.h.
Stek je implementiran u datoteci stacklib.c koriscenjem povezane liste zbog efikasnijeg koriscenja memorije.
U datoteci bmp.c implementiran je modul za ucitavanje slike (koja je tipa monohromatski bmp) u formi matrice nula i jedinica.
Datoteka encoding_decoding.c sadrzi 2 funkcije encodePoint i decodePoint koje nam sluze za pakovanje koordinata u jednu int vrednost
i njihovo dekodiranje iz int vrednosti. Ovo olaksava posle rukovanje sa koordinatama u trenucima kad treba da ih stavljamo i skidamo sa steka.
U longest_line.c datoteci se nalaze funckije dfs koja vrsi dfs pretragu i funkcija findLongestLine koja uz pomoc dfs-a pronalazi najduzu
liniju u slici.
U main.c se nalazi funckija printMatrix koja ispisuje binarnu matricu kako bi imali vizuelnu predstavu ucitane slike,
pored toga u main-u se ucitava slika pomocu funkcije LoadBitmapFile iz bmp.c, zatim se ispisuje matrica i poziva funkcija findLongestLine
koja vraca duzinu najduze linije u pikselima.

---------------------------------------------------------------------------------------------------------------------------------------------

MISRA pravila koja su ignorisana:

    -MISRA-C:2004 20.9/R - <stdio.h> biblioteka je neophodna zbog vizuelne reprezentacije ucitane matrice i zbog obavestenja o duzini najduze lnije
    -MISRA-C:2004 20.4/R - Dinamicko zauzimanje memorije je neophodno zbog zauzimanja mesta za niz gde ce biti ucitana slika
    -MISRA-C:2004 8.1/R - Funckija je dovoljno mala da ne zahteva da se izdvaja u poseban modul koji sadrzi samo deklaraciju funkcije
    -MISRA-C:2004 5.7/A - Zbog citljivosti na nekim mestima su imena identifikatora ponovljena
---------------------------------------------------------------------------------------------------------------------------------------------

Testiranje: Testiranje je odradjeno nad vise slika razlicite velicine. Kod nekih cilj je da se pokaze da ucitavanje dobro radi ali je broj
jedinica suvise velik da bi se rucno prebrojao i samim tim nije lako na tom primeru odraditi validaciju. Iz tog razloga validacija ispravnosti modula
koji racuna duzinu najduze linije je odradjena na jednostavnom primeru gde je lako rucno prebrojati jedinice i utvrditi da program radi ispravno.

---------------------------------------------------------------------------------------------------------------------------------------------

Prevodjenje: gcc --static -o app main.c longest_line.c bmp.c stacklib.c encoding_decoding.c -L. -lstack
Pokretanje: ./app [ime datoteke].bmp

*/





#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "stacklib.h"
#include "longest_line.h"

static const int_least8_t ARG_NUM = 2;


/* funckija za ispis ucitane binarne matrice */
void printMatrix(uint_least8_t* bitmapData, int width, int height) {
    printf("Ucitana binarna matrica:\n");
    for (int_least32_t y = height-1; y >= 0; y--) {
        for (int_least32_t x = 0; x < width; x++) {
            printf("%d ", bitmapData[y * width + x]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    BITMAPFILEHEADER bitmapFileHeader;
    BITMAPINFOHEADER bitmapInfoHeader;
    uint_least8_t* bitmapData;

    if (argc != ARG_NUM)
    {
        printf("Unesite ime datoteke\n");
        return EXIT_FAILURE;
    }

    /*Ucitavanje slike*/
    bitmapData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
    if (!bitmapData)
    {
        printf("Error! Can't open input bitmap file: %s\n", argv[1]);
		return EXIT_FAILURE;
    }

    /*Ispis binarne matrice*/
    printMatrix(bitmapData, bitmapInfoHeader.biWidth, abs(bitmapInfoHeader.biHeight));


    int_least32_t longestLine = findLongestLine(bitmapData, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight);
    if (longestLine < 0)
    {
        printf("Greska u pronalazenju najduze linije!.\n");
    }
    else
    {
        printf("Najduza linija je %d piksela dugacka\n", longestLine);
    }

    free(bitmapData);

    return 0;
}
