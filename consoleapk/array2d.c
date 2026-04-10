#include "array2d.h"
#include <stdio.h>

char text[MAX_BARIS][MAX_KOLOM];
void initBuffer()
{
    for (int i = 0; i < MAX_BARIS; i++)
    {
        for (int j = 0; j < MAX_KOLOM; j++)
        {
            text[i][j] = '\0';
        }
    }
}

void insertChar(int baris, int kolom, char c)
{
    for (int i = MAX_KOLOM - 1; i > kolom; i--)
    {
        text[baris][i] = text[baris][i - 1];
    }
    text[baris][kolom] = c;
}

void deleteChar(int baris, int kolom)
{
    for (int i = kolom; i < MAX_KOLOM - 1; i++)
    {
        text[baris][i] = text[baris][i + 1];
    }

   text[baris][MAX_KOLOM - 1] = '\0';
}

void displayBuffer()
{
    for (int i = 0; i < MAX_BARIS; i++)
    {
        if (text[i][0] == '\0')
        {
            break;
        }

        for (int j = 0; j < MAX_KOLOM; j++)
        {
            if (text[i][j] == '\0')
            {
                break;
            }

            printf("%c", text[i][j]);
        }

        printf("\n");
    }
}
