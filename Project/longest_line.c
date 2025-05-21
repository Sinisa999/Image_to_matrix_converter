#include "longest_line.h"
#include "encoding_decoding.h"
#include "stacklib.h"


int_least32_t dx[] = {1, -1, 0, 0};
int_least32_t dy[] = {0, 0, 1, -1};


int_least32_t dfs(uint_least8_t* image, int_least32_t width, int_least32_t height, int_least32_t startX, int_least32_t startY, uint_least8_t* visited)
{
    node* stack = NULL;

    /*stavljamo pocetnu tacku na stek*/
    push(&stack, encodePoint(startX, startY, width));

    int_least32_t lineLength = 0;

    while (!isEmpty(&stack))
    {
        /*skidamo element sa vrha steka*/
        int_least32_t encodedPoint = peek(&stack);
        pop(&stack);

        /*dekodujemo koordinate*/
        int_least32_t x;
        int_least32_t y;
        decodePoint(encodedPoint, width, &x, &y);

        /*Preskacemo tacku koja je vec posecena*/
        if (visited[y * width + x])
        {
            continue;
        }

        /*Oznacavanje tacke koja je posecena*/
        visited[y * width + x] = 1;
        lineLength++;

        /*ispitivanje sva 4 suseda (gore, dole, levo, desno)*/
        for (int_least32_t i = 0; i < 4; i++)
        {
            int_least32_t newX = x + dx[i];
            int_least32_t newY = y + dy[i];

            /*porvera da li su susedi u okviru slike i da li su deo linije*/
            if (newX >= 0 && newX < width && newY >= 0 && newY < height && image[newY * width + newX] == 1 && !visited[newY * width + newX])
            {
                push(&stack, encodePoint(newX, newY, width));
            }
        }
    }
    return lineLength;
}

/*Funckija koja pronalazi najduzu liniju u slici*/
int_least32_t findLongestLine(uint_least8_t* image, int_least32_t width, int_least32_t height)
{
    /*pravljenje niza posecenih piksela*/
    uint_least8_t* visited = (uint_least8_t*)calloc(width * height, sizeof(uint_least8_t));

    if (!visited)
    {
        printf("Error! Memory allocation failed.\n");
        return -1;
    }


    int_least32_t longestLine = 0;

    /*prolazak kroz svaki piksel u slici*/
    for (int_least32_t y = 0; y < height; y++)
    {
        for (int_least32_t x = 0; x < width; x++)
        {
            /*ako je piksel 1 i ako nije posecenm, primeniti dfs*/
            if (image[y * width + x] == 1 && !visited[y * width + x])
            {
                int_least32_t length = dfs(image, width, height, x, y, visited);
                printf("Pronadjena linija duzine %d sa pocetkom u (%d, %d)\n", length, x, y);
                if(length > longestLine)
                {
                    longestLine = length;
                }
            }
        }
    }

    /*Oslobadjanje niza posecenih*/
    free(visited);

    return longestLine;


}


