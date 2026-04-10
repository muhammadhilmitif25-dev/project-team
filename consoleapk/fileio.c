#include <stdio.h>
#include "fileio.h"
#include "editor.h"

void SimpanKeFile() {
    FILE *fptr = fopen(namaFileDefault, "w");
    if (fptr == NULL) {
        printf(">> Gagal membuka file untuk disimpan!\n");
        return;
    }
    fprintf(fptr, "%s", buffer);
    fclose(fptr);
    isDirty = false;
    printf(">> Berhasil disimpan ke %s\n", namaFileDefault);
}

void SaveAs() {
    printf("--- FITUR SAVE AS ---\n");
    printf("Masukkan nama file baru (akhiri dengan .txt): ");
    scanf("%s", namaFileDefault);
    SimpanKeFile(); 
}

void BukaDariFile() {
    FILE *fptr = fopen(namaFileDefault, "r");
    if (fptr == NULL) {
        printf(">> File %s tidak ditemukan!\n", namaFileDefault);
        return;
    }
    fgets(buffer, sizeof(buffer), fptr);
    fclose(fptr);
    isDirty = false;
    printf(">> File %s berhasil dimuat ke layar.\n", namaFileDefault);
}