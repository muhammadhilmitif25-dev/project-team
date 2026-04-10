#include <stdio.h>
#include <string.h>
#include "searchfile.h"
#include "editor.h"

void CariKata() {
    char kata[50];
    printf("Masukkan kata yang dicari: ");
    scanf(" %s", kata);

    if (strstr(buffer, kata) != NULL) {
        printf(">> Hasil: Kata '%s' DITEMUKAN!\n", kata);
    } else {
        printf(">> Hasil: Kata tidak ada.\n");
    }
}