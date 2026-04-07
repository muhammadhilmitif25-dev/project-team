#include <stdio.h>
#include "array2d.h"
#include "boolean.h"

int showMainMenu();
int openFileMenu();
void createNewFile();
void searchFile();
void exitProgram();

// Menu utama
int showMainMenu()
{
    int pilih;
    printf("\n=== MAIN MENU ===\n");
    printf("1. Open File\n");
    printf("2. Exit\n");
    printf("Pilih: ");
    scanf("%d", &pilih);
    return pilih;
}

// Sub menu Open File
int openFileMenu()
{
    int pilih;

    do
    {
        printf("\n=== OPEN FILE ===\n");
        printf("1. New File\n");
        printf("2. Search File\n");
        printf("3. Back\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        switch (pilih)
        {
        case 1:
            createNewFile();
            break;
        case 2:
            searchFile();
            break;
        case 3:
            printf("Kembali ke menu utama...\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }

    } while (pilih != 3);

    return 0;
}

// New file

void createNewFile()
{
    initBuffer();

    int row = 0;
    int col = 0;
    char c;
    getchar(); // buang ENTER sisa dari scanf
    printf("Mulai mengetik (ENTER untuk baris baru, ESC untuk keluar)\n");

    while (1)
    {
        c = getchar();

        if (c == 27)
        { // ESC
            break;
        }

        if (c == '\n')
        {
            row++;
            col = 0;
        }
        else
        {
            insertChar(row, col, c);
            col++;
        }
    }

    displayBuffer();
    
}

// Search file
void searchFile()
{
    printf("\n[Mencari file...]\n");
}

// Exit
void exitProgram()
{
    printf("\n[Keluar dari program]\n");
}

// mainnya
int main()
{
    int pilihan;

    do
    {
        pilihan = showMainMenu();

        switch (pilihan)
        {
        case 1:
            openFileMenu();
            break;
        case 2:
            exitProgram();
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }

    } while (pilihan != 2);

    return 0;
}