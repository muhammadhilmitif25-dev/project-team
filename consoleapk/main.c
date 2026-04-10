#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "editor.h"
#include "cursor.h"
#include "fileio.h"
#include "buffer.h"
#include "searchfile.h"

// Inisialisasi variabel global di sini (Hanya sekali)
bool isDirty = false;
char buffer[1000] = ""; 
char namaFileDefault[100] = "catatan.txt"; 

int main() {
    int menu;
    while (1) {
        printf("\n=== NOTEPAD CONSOLE CKA (PRO) ===\n");
        printf("Isi Notepad: [%s]\n", buffer);
        printf("Status: %s\n", isDirty ? "DIRTY (Butuh Save)" : "CLEAN (Aman)");
        printf("---------------------------------\n");
        printf("1. Ketik Teks (Arbitrary Insertion)\n");
        printf("2. Save File (Simpan)\n");
        printf("3. Save As (Nama Baru)\n");
        printf("4. Open File (Buka)\n");
        printf("5. Search (Cari Kata)\n");
        printf("6. Lembar Baru (Correct Navigation)\n");
        printf("7. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &menu);

        if (menu == 1) {
            printf("Masukkan teks: ");
            scanf(" %[^\n]s", buffer);
            isDirty = true;
        } 
        else if (menu == 2) SimpanKeFile();
        else if (menu == 3) SaveAs();
        else if (menu == 4) BukaDariFile();
        else if (menu == 5) CariKata();
        else if (menu == 6) JalankanFiturNew();
        else if (menu == 7) break;
    }
    return 0;
}