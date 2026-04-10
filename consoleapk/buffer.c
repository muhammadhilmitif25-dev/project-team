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

    // --- SKENARIO 1: Hapus di tengah baris (col > 0) ---
    // (BAGIAN INI SUDAH BENAR DARI SEBELUMNYA, PERTAHANKAN)
    if (col > 0) {
        int wasFull = (b->text[row][MAX_KOLOM - 1] != '\0');
        
        b->cur.klm--;
        col--; 

        for (int j = col; j < MAX_KOLOM - 1; j++) {
            b->text[row][j] = b->text[row][j + 1];
        }
        b->text[row][MAX_KOLOM - 1] = '\0';

        if (wasFull) {
            int curr_r = row;
            while (curr_r < MAX_BARIS - 1) {
                if (b->text[curr_r + 1][0] != '\0') {
                    b->text[curr_r][MAX_KOLOM - 1] = b->text[curr_r + 1][0];
                    int nextWasFull = (b->text[curr_r + 1][MAX_KOLOM - 1] != '\0');
                    
                    for (int k = 0; k < MAX_KOLOM - 1; k++) {
                        b->text[curr_r + 1][k] = b->text[curr_r + 1][k + 1];
                    }
                    b->text[curr_r + 1][MAX_KOLOM - 1] = '\0';

                    if (b->text[curr_r + 1][0] == '\0') {
                        for (int i = curr_r + 1; i < MAX_BARIS - 1; i++) {
                            for (int j = 0; j < MAX_KOLOM; j++) {
                                b->text[i][j] = b->text[i + 1][j];
                            }
                        }
                        for (int j = 0; j < MAX_KOLOM; j++) b->text[MAX_BARIS - 1][j] = '\0';
                        break;
                    }
                    if (!nextWasFull) break; 
                    curr_r++;
                } else {
                    break;
                }
            }
        }
    } 
    // --- SKENARIO 2: Gabung Baris / Backspace di Kolom 0 ---
    else if (row > 0) {
        int prev = row - 1;
        
        // KUNCI: Cek apakah baris INI tadinya full?
        // Kalau nggak full, dia HARAM narik baris di bawahnya!
        int rowWasFull = (b->text[row][MAX_KOLOM - 1] != '\0');
        
        int lastPos = 0;
        while (lastPos < MAX_KOLOM && b->text[prev][lastPos] != '\0') {
            lastPos++;
        }

        b->cur.brs = prev;
        b->cur.klm = lastPos;

        int k = 0;
        while (k < MAX_KOLOM && b->text[row][k] != '\0' && lastPos + k < MAX_KOLOM) {
            b->text[prev][lastPos + k] = b->text[row][k];
            k++;
        }

        int charsMoved = k;

        if (charsMoved > 0) {
            for (int i = 0; i < MAX_KOLOM - charsMoved; i++) {
                b->text[row][i] = b->text[row][i + charsMoved];
            }
            for (int i = MAX_KOLOM - charsMoved; i < MAX_KOLOM; i++) {
                b->text[row][i] = '\0';
            }
        }

        if (b->text[row][0] == '\0') {
            for (int i = row; i < MAX_BARIS - 1; i++) {
                for (int j = 0; j < MAX_KOLOM; j++) {
                    b->text[i][j] = b->text[i + 1][j];
                }
            }
            for (int j = 0; j < MAX_KOLOM; j++) b->text[MAX_BARIS - 1][j] = '\0';
        } else {
            // SOLUSI: Cuma narik baris bawah kalau rowWasFull == 1 (aslinya Auto-Wrap)
            if (rowWasFull) {
                int curr_r = row;
                while (curr_r < MAX_BARIS - 1) {
                    int len = 0;
                    while (len < MAX_KOLOM && b->text[curr_r][len] != '\0') len++;
                    int gaps = MAX_KOLOM - len;

                    if (gaps > 0 && b->text[curr_r + 1][0] != '\0') {
                        int moved = 0;
                        while (moved < gaps && b->text[curr_r + 1][moved] != '\0') {
                            b->text[curr_r][len + moved] = b->text[curr_r + 1][moved];
                            moved++;
                        }

                        for (int i = 0; i < MAX_KOLOM - moved; i++) {
                            b->text[curr_r + 1][i] = b->text[curr_r + 1][i + moved];
                        }
                        for (int i = MAX_KOLOM - moved; i < MAX_KOLOM; i++) {
                            b->text[curr_r + 1][i] = '\0';
                        }

                        if (b->text[curr_r + 1][0] == '\0') {
                            for (int i = curr_r + 1; i < MAX_BARIS - 1; i++) {
                                for (int j = 0; j < MAX_KOLOM; j++) {
                                    b->text[i][j] = b->text[i + 1][j];
                                }
                            }
                            for (int j = 0; j < MAX_KOLOM; j++) b->text[MAX_BARIS - 1][j] = '\0';
                            break;
                        }
                        curr_r++;
                    } else {
                        break;
                    }
                }
            }
        }
    }
    b->isSaved = 0;
}
void newLine(Buffer *b) {
    if (countTotalChars(b) >= (MAX_BARIS * MAX_KOLOM) || b->cur.brs >= MAX_BARIS - 1) return;

    int row = b->cur.brs;
    int col = b->cur.klm;

    // KUNCI: Cek apakah baris ini aslinya penuh? 
    // Kalau penuh, berarti baris bawahnya adalah sambungan kata yang terputus.
    int wasFull = (b->text[row][MAX_KOLOM - 1] != '\0');

    // 1. Geser semua baris di bawah kursor TURUN 1 level secara UTUH.
    for (int i = MAX_BARIS - 1; i > row + 1; i--) {
        for (int j = 0; j < MAX_KOLOM; j++) {
            b->text[i][j] = b->text[i - 1][j];
        }
    }

    // 2. Kosongkan baris baru yang terbentuk
    for (int j = 0; j < MAX_KOLOM; j++) {
        b->text[row + 1][j] = '\0';
    }

    // 3. Pindahkan sisa karakter di KANAN kursor ke baris baru tersebut
    int k = 0;
    for (int j = col; j < MAX_KOLOM; j++) {
        if (b->text[row][j] != '\0') {
            b->text[row + 1][k++] = b->text[row][j];
            b->text[row][j] = '\0'; // Hapus dari baris lama
        }
    }

    // 4. Update Kursor ke awal baris baru
    b->cur.brs++;
    b->cur.klm = 0;
    b->isSaved = 0;

    // 5. RIPPLE UP: Jika aslinya penuh, tarik sisa katanya (misal 'at') ke baris baru ('farah')
    if (wasFull) {
        int curr_r = row + 1; 
        while (curr_r < MAX_BARIS - 1) {
            int len = 0;
            while (len < MAX_KOLOM && b->text[curr_r][len] != '\0') len++;
            int gaps = MAX_KOLOM - len;

            if (gaps > 0 && b->text[curr_r + 1][0] != '\0') {
                int moved = 0;
                while (moved < gaps && b->text[curr_r + 1][moved] != '\0') {
                    b->text[curr_r][len + moved] = b->text[curr_r + 1][moved];
                    moved++;
                }

                for (int i = 0; i < MAX_KOLOM - moved; i++) {
                    b->text[curr_r + 1][i] = b->text[curr_r + 1][i + moved];
                }
                for (int i = MAX_KOLOM - moved; i < MAX_KOLOM; i++) {
                    b->text[curr_r + 1][i] = '\0';
                }

                if (b->text[curr_r + 1][0] == '\0') {
                    for (int i = curr_r + 1; i < MAX_BARIS - 1; i++) {
                        for (int j = 0; j < MAX_KOLOM; j++) {
                            b->text[i][j] = b->text[i + 1][j];
                        }
                    }
                    for (int j = 0; j < MAX_KOLOM; j++) b->text[MAX_BARIS - 1][j] = '\0';
                    break; 
                }
                curr_r++;
            } else {
                break;
            }
        }
    }
}

/* --- DISPLAY --- */
void displayBuffer(Buffer *b) {
    for (int i = 0; i < MAX_BARIS; i++) {
        // Cek apakah baris ini ada isinya?
        int adaIsi = 0;
        for (int k = 0; k < MAX_KOLOM; k++) {
            if (b->text[i][k] != '\0' && b->text[i][k] != ' ') {
                adaIsi = 1;
                break;
            }
        }
        
        // Skip baris kosong biar nggak menuai layar (kecuali baris kursor)
        if (!adaIsi && i != b->cur.brs) continue;

        for (int j = 0; j < MAX_KOLOM; j++) {
            // Tampilkan Kursor
            if (i == b->cur.brs && j == b->cur.klm) printf("|");

            // Tampilkan Karakter
            if (b->text[i][j] != '\0') {
                printf("%c", b->text[i][j]);
            } else {
                // Kalo null, print spasi HANYA kalo posisinya di kiri kursor
                if (i == b->cur.brs && j < b->cur.klm) printf(" ");
            }
        }
        printf("\n");
    }
}