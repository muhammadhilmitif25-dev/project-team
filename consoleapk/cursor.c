#include "kursor.h"
#include "array2d.h"
#include <stdbool.h>

// Variabel pendukung
bool isDirty = false;
extern HWND hEdit;

void JalankanFitur(HWND hwnd) {
    if (isDirty) {
        if (MessageBox(hwnd, "Simpan perubahan?", "Konfirmasi", MB_YESNO) == IDYES) {
            isDirty = false;
        }
    }
    // 1. Bersihkan tampilan di layar
    SetWindowText(hEdit, ""); 

    // 2. Bersihkan data di memori (Array 2D)
    initBuffer();

    // 3. Reset status perubahan
    isDirty = false;
}
