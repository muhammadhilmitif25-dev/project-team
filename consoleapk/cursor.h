#ifndef CURSOR_H
#define CURSOR_H

typedef struct {
    int brs; // Baris kursor
    int klm; // Kolom kursor
} Cursor;

// Inisialisasi kursor ke (0,0)
void initCursor(Cursor *c);

#endif