#include <stdio.h>
#include <string.h>
#include "editor.h"
#include "fileio.h"

void JalankanFiturNew() {
    if (isDirty) {
        char pilihan;
        printf("\n[PERINGATAN] Data belum disimpan! Simpan dulu ke %s? (y/n): ", namaFileDefault);
        scanf(" %c", &pilihan);

        if (pilihan == 'y' || pilihan == 'Y') {
            SimpanKeFile(); 
        }
    }
    strcpy(buffer, ""); 
    isDirty = false;
    printf("\n>> Lembar kerja baru siap.\n");
}