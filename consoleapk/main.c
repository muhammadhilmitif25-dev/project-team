#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_COLS 256

char buffer[MAX_LINES][MAX_COLS];
int line_count = 0;

// fungsi simpan ke file
void saveToFile(char *filename)
{
    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        printf("Gagal membuka file!\n");
        return;
    }

    for (int i = 0; i < line_count; i++)
    {
        fprintf(f, "%s\n", buffer[i]);
    }

    fclose(f);
    printf("File berhasil disimpan!\n");
}

int main_vim(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: myapp <filename>\n");
        return 1;
    }

    char *filename = argv[1];
    char input[MAX_COLS];

    printf("Mini Text Editor (Vim-style)\n");
    printf("Command:\n");
    printf(":q   = keluar\n");
    printf(":w   = simpan\n");
    printf(":wq  = simpan & keluar\n\n");

    while (1)
    {
        printf("%d > ", line_count + 1);
        fgets(input, MAX_COLS, stdin);

        // hapus newline
        input[strcspn(input, "\n")] = '\0';

        // cek command
        if (input[0] == ':')
        {
            if (strcmp(input, ":q") == 0)
            {
                printf("Keluar tanpa simpan...\n");
                break;
            }
            else if (strcmp(input, ":w") == 0)
            {
                saveToFile(filename);
            }
            else if (strcmp(input, ":wq") == 0)
            {
                saveToFile(filename);
                printf("Keluar...\n");
                break;
            }
            else
            {
                printf("Command tidak dikenal!\n");
            }
        }
        else
        {
            // simpan ke buffer
            if (line_count < MAX_LINES)
            {
                strcpy(buffer[line_count], input);
                line_count++;
            }
            else
            {
                printf("Buffer penuh!\n");
            }
        }
    }

    return 0;
}