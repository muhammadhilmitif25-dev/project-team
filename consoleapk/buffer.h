#ifndef BUFFER_H
#define BUFFER_H

#include "cursor.h" // 🔥 Harus include ini

#define MAX_BARIS 100
#define MAX_KOLOM 100

typedef struct {
    char text[MAX_BARIS][MAX_KOLOM];
    Cursor cur;   // 🔥 Sekarang kursor jadi bagian dari buffer
    int isSaved; 
} Buffer;

void initBuffer(Buffer *b);
void insertChar(Buffer *b, char c);
void deleteChar(Buffer *b);
void newLine(Buffer *b);
void displayBuffer(Buffer *b);
int countTotalChars(Buffer *b);

// Fungsi navigasi sekarang dipindah logikanya ke buffer karena butuh cek teks
void movekiri(Buffer *b);
void movekanan(Buffer *b);
void moveatas(Buffer *b);
void movebawah(Buffer *b);

#endif