#include "cursor.h"

void initCursor(Cursor *c) {
    c->brs = 0;
    c->klm = 0;
}

// Fungsi pembantu agar kursor tidak keluar batas MAX
void setCursorPos(Cursor *c, int newBrs, int newKlm) {
    if (newBrs >= 0 && newBrs < 10) c->brs = newBrs;
    if (newKlm >= 0 && newKlm <= 10) c->klm = newKlm;
}