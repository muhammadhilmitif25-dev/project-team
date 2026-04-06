#include "kursor.h"
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
    SetWindowText(hEdit, ""); 
    isDirty = false;
}
