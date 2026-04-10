#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Variabel Global
bool isDirty = false;
char buffer[1000] = ""; // "Jendela Putih" di RAM
char namaFileDefault[] = "catatan.txt"; 


// 1. Fungsi Save (Menyimpan teks ke file)
void SimpanKeFile() {
    FILE *fptr = fopen(namaFileDefault, "w"); // "w" = write/tulis
    if (fptr == NULL) {
        printf(">> Gagal membuka file untuk disimpan!\n");
        return;
    }
    fprintf(fptr, "%s", buffer); // Pindahkan data dari RAM (buffer) ke Harddisk
    fclose(fptr);
    isDirty = false; // Status jadi CLEAN karena sudah aman di harddisk
    printf(">> Berhasil disimpan ke %s\n", namaFileDefault);
}

// 2. Fungsi Open (Membuka teks dari file)
void BukaDariFile() {
    FILE *fptr = fopen(namaFileDefault, "r"); // "r" = read/baca
    if (fptr == NULL) {
        printf(">> File %s tidak ditemukan!\n", namaFileDefault);
        return;
    }
    fgets(buffer, sizeof(buffer), fptr); // Ambil teks dari harddisk masukkan ke RAM
    fclose(fptr);
    isDirty = false; // Karena baru buka, belum ada perubahan baru
    printf(">> File %s berhasil dimuat ke layar.\n", namaFileDefault);
}

// 3. Fungsi Search (Mencari kata)
void CariKata() {
    char kata[50];
    printf("Masukkan kata yang dicari: ");
    scanf(" %s", kata);

    // strstr = fungsi C untuk mencari posisi kata dalam teks
    if (strstr(buffer, kata) != NULL) {
        printf(">> Hasil: Kata '%s' DITEMUKAN!\n", kata);
    } else {
        printf(">> Hasil: Kata tidak ada.\n");
    }
}


void JalankanFiturNew() {
    if (isDirty) {
        char pilihan;
        printf("\n[PERINGATAN] Data belum disimpan! Simpan dulu ke %s? (y/n): ", namaFileDefault);
        scanf(" %c", &pilihan);

        if (pilihan == 'y' || pilihan == 'Y') {
            SimpanKeFile(); // Panggil fungsi save sebelum buat lembar baru
        }
    }
    strcpy(buffer, ""); // Reset buffer
    isDirty = false;
    printf("\n>> Lembar kerja baru siap.\n");
}

int main() {
    int menu;
    while (1) {
        printf("\n=== NOTEPAD CONSOLE CKA (PRO) ===\n");
        printf("Isi Notepad: [%s]\n", buffer);
        printf("Status: %s\n", isDirty ? "DIRTY (Butuh Save)" : "CLEAN (Aman)");
        printf("---------------------------------\n");
        printf("1. Ketik Teks (Arbitrary Insertion)\n");
        printf("2. Save File (Simpan)\n");
        printf("3. Open File (Buka)\n");
        printf("4. Search (Cari Kata)\n");
        printf("5. Lembar Baru (Correct Navigation)\n");
        printf("6. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &menu);

        if (menu == 1) {
            printf("Masukkan teks: ");
            scanf(" %[^\n]s", buffer);
            isDirty = true;
        } 
        else if (menu == 2) {
            SimpanKeFile();
        } 
        else if (menu == 3) {
            BukaDariFile();
        }
        else if (menu == 4) {
            CariKata();
        }
        else if (menu == 5) {
            JalankanFiturNew();
        } 
        else if (menu == 6) {
            break;
        }
    }
    return 0;
}