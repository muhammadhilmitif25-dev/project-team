#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "buffer.h"
#include "boolean.h"

// Deklarasi Fungsi Menu
int showMainMenu();
int openFileMenu();
void createNewFile();
void searchFile();
void exitProgram();

int main() {
    int pilihan;
    do {
        pilihan = showMainMenu();
        switch (pilihan) {
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

// --- FUNGSI EDITOR (Pindahan dari main lama lu) ---
void createNewFile() {
    Buffer b;
    initBuffer(&b);
    system("cls");
    
    printf("--- NEW FILE (Mode Editor) ---\n");
    printf("ESC: Keluar | Arrows: Navigasi | Backspace: Hapus\n\n");
    displayBuffer(&b);

    while (1) {
        int c = getch();

        // 1. ESC - Keluar
        if (c == 27) {
            if (b.isSaved == 0) {
                printf("\nBelum disave! Keluar? (y/n): ");
                char pilih = getch();
                if (pilih == 'y' || pilih == 'Y') break;
            } else {
                break;
            }
        }
        // 2. ARROW KEYS
        else if (c == 224) {
            int arrow = getch();
            if (arrow == 75) movekiri(&b);
            else if (arrow == 77) movekanan(&b);
            else if (arrow == 72) moveatas(&b);
            else if (arrow == 80) movebawah(&b);
        }
        // 3. BACKSPACE
        else if (c == 8) {
            deleteChar(&b);
        }
        // 4. ENTER
        else if (c == 13) {
            newLine(&b);
        }
        // 5. KARAKTER BIASA
        else if (c >= 32 && c <= 126) {
            insertChar(&b, (char)c);
        }

        // REFRESH DISPLAY
        system("cls");
        printf("--- EDITOR MODE (10x10) ---\n");
        displayBuffer(&b);
    }
}

// --- SISA FUNGSI MENU ---
int showMainMenu() {
    int pilih;
    printf("\n=== MAIN MENU ===\n");
    printf("1. Open File\n");
    printf("2. Exit\n");
    printf("Pilih: ");
    scanf("%d", &pilih);
    return pilih;
}

int openFileMenu() {
    int pilih;
    do {
        printf("\n=== OPEN FILE ===\n");
        printf("1. New File\n");
        printf("2. Search File\n");
        printf("3. Back\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                createNewFile(); // Panggil fungsi editor di sini
                break;
            case 2:
                searchFile();
                break;
            case 3:
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilih != 3);
    return 0;
}

void searchFile() { printf("\n[Mencari file...]\n"); }
void exitProgram() { printf("\n[Keluar dari program]\n"); }