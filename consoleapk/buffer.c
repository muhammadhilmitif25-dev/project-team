#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

/* --- INISIALISASI --- */
void initBuffer(Buffer *b) {
    for (int i = 0; i < MAX_BARIS; i++) {
        for (int j = 0; j < MAX_KOLOM; j++) {
            b->text[i][j] = '\0';
        }
    }
    // Inisialisasi kursor lewat sub-struct cur
    b->cur.brs = 0;
    b->cur.klm = 0;
    b->isSaved = 1;
}

/* --- FUNGSI UTILITY --- */
int countTotalChars(Buffer *b) {
    int total = 0;
    for (int i = 0; i < MAX_BARIS; i++) {
        for (int j = 0; j < MAX_KOLOM; j++) {
            if (b->text[i][j] != '\0') total++;
        }
    }
    return total;
}

/* --- MANIPULASI TEKS --- */
void insertChar(Buffer *b, char c) {
    // 🔥 SATPAM 100 KARAKTER (Lockdown Total)
    if (countTotalChars(b) >= (MAX_BARIS * MAX_KOLOM)) return;

    int row = b->cur.brs;
    int col = b->cur.klm;

    int len = 0;
    while (len < MAX_KOLOM && b->text[row][len] != '\0') len++;

    if (len >= MAX_KOLOM) {
        // Efek Overflow (Domino)
        char lastChar = b->text[row][MAX_KOLOM - 1];
        for (int i = MAX_KOLOM - 1; i > col; i--) {
            b->text[row][i] = b->text[row][i - 1];
        }
        b->text[row][col] = c;

        if (row < MAX_BARIS - 1) {
            int oldRow = b->cur.brs;
            int oldCol = b->cur.klm;
            
            b->cur.brs = row + 1;
            b->cur.klm = 0;
            insertChar(b, lastChar);

            // Balikin kursor ke posisi ngetik yang asli
            if (oldCol < MAX_KOLOM - 1) {
                b->cur.brs = oldRow;
                b->cur.klm = oldCol + 1;
            } else {
                b->cur.brs = oldRow + 1;
                b->cur.klm = 0;
            }
        }
    } else {
        // Insert Biasa
        for (int i = len; i > col; i--) {
            if (i < MAX_KOLOM) b->text[row][i] = b->text[row][i - 1];
        }
        b->text[row][col] = c;
        b->cur.klm++;

        // Auto-wrap kursor
        if (b->cur.klm >= MAX_KOLOM && b->cur.brs < MAX_BARIS - 1) {
            b->cur.brs++;
            b->cur.klm = 0;
        }
    }
    b->isSaved = 0;
}

void deleteChar(Buffer *b) {
    int row = b->cur.brs;
    int col = b->cur.klm;

    if (row == 0 && col == 0) return;

    // 1. Hitung Posisi Linear Kursor
    int currentLinearPos = 0;
    for (int i = 0; i < row; i++) {
        int len = 0;
        while (len < MAX_KOLOM && b->text[i][len] != '\0') len++;
        currentLinearPos += len;
    }
    currentLinearPos += col;
    int deleteLinearIndex = currentLinearPos - 1;

    // 2. Ambil semua teks, skip karakter yang dihapus (Ripple Effect)
    char tempSisa[MAX_BARIS * MAX_KOLOM + 1];
    int k = 0, charCounter = 0;
    for (int i = 0; i < MAX_BARIS; i++) {
        for (int j = 0; j < MAX_KOLOM && b->text[i][j] != '\0'; j++) {
            if (charCounter != deleteLinearIndex) {
                tempSisa[k++] = b->text[i][j];
            }
            charCounter++;
        }
        // Wipe Baris
        for (int j = 0; j < MAX_KOLOM; j++) b->text[i][j] = '\0';
    }
    tempSisa[k] = '\0';

    // 3. Tulis Ulang & Set Kursor Baru
    b->cur.brs = 0; b->cur.klm = 0;
    for (int i = 0; i < k; i++) {
        insertChar(b, tempSisa[i]);
    }

    int runningPos = 0;
    for (int i = 0; i < MAX_BARIS; i++) {
        int len = 0;
        while (len < MAX_KOLOM && b->text[i][len] != '\0') len++;
        if (deleteLinearIndex <= runningPos + len) {
            b->cur.brs = i;
            b->cur.klm = deleteLinearIndex - runningPos;
            break;
        }
        runningPos += len;
    }
    b->isSaved = 0;
}

void newLine(Buffer *b) {
    if (countTotalChars(b) >= (MAX_BARIS * MAX_KOLOM) || b->cur.brs >= MAX_BARIS - 1) return;

    char tempSisa[MAX_BARIS * MAX_KOLOM + 1];
    int k = 0;
    for (int i = b->cur.brs; i < MAX_BARIS; i++) {
        int startCol = (i == b->cur.brs) ? b->cur.klm : 0;
        for (int j = startCol; j < MAX_KOLOM && b->text[i][j] != '\0'; j++) {
            tempSisa[k++] = b->text[i][j];
        }
        for (int j = startCol; j < MAX_KOLOM; j++) b->text[i][j] = '\0';
    }
    tempSisa[k] = '\0';

    b->cur.brs++; b->cur.klm = 0;
    int targetRow = b->cur.brs;
    for (int i = 0; i < k; i++) insertChar(b, tempSisa[i]);

    b->cur.brs = targetRow;
    b->cur.klm = 0;
    b->isSaved = 0;
}

/* --- NAVIGASI --- */
void movekiri(Buffer *b) {
    if (b->cur.klm > 0) {
        b->cur.klm--;
    } else if (b->cur.brs > 0) {
        b->cur.brs--;
        int len = 0;
        while (len < MAX_KOLOM && b->text[b->cur.brs][len] != '\0') len++;
        b->cur.klm = len;
    }
}

void movekanan(Buffer *b) {
    int len = 0;
    while (len < MAX_KOLOM && b->text[b->cur.brs][len] != '\0') len++;
    if (b->cur.klm < len) {
        b->cur.klm++;
    } else if (b->cur.brs < MAX_BARIS - 1 && b->text[b->cur.brs + 1][0] != '\0') {
        b->cur.brs++;
        b->cur.klm = 0;
    }
}

void moveatas(Buffer *b) {
    if (b->cur.brs > 0) {
        b->cur.brs--;
        int len = 0;
        while (len < MAX_KOLOM && b->text[b->cur.brs][len] != '\0') len++;
        if (b->cur.klm > len) b->cur.klm = len;
    }
}

void movebawah(Buffer *b) {
    if (b->cur.brs < MAX_BARIS - 1 && b->text[b->cur.brs + 1][0] != '\0') {
        b->cur.brs++;
        int len = 0;
        while (len < MAX_KOLOM && b->text[b->cur.brs][len] != '\0') len++;
        if (b->cur.klm > len) b->cur.klm = len;
    }
}

/* --- DISPLAY --- */
void displayBuffer(Buffer *b) {
    for (int i = 0; i < MAX_BARIS; i++) {
        if (b->text[i][0] == '\0' && i != b->cur.brs) continue;
        for (int j = 0; j <= MAX_KOLOM; j++) {
            if (i == b->cur.brs && j == b->cur.klm) printf("|");
            if (j < MAX_KOLOM) {
                if (b->text[i][j] == '\0') break;
                printf("%c", b->text[i][j]);
            }
        }
        printf("\n");
    }
}