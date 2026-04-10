#ifndef ARRAY2D_H
#define ARRAY2D_H

#define MAX_BARIS 100
#define MAX_KOLOM 100

extern char text[MAX_BARIS][MAX_KOLOM];

void initBuffer();
void insertChar(int baris, int kolom, char c);
void deleteChar(int baris, int kolom);
void displayBuffer();
#endif