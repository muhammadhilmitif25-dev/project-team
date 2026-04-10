#ifndef EDITOR_H
#define EDITOR_H
#include <stdbool.h>

// Variabel Global supaya bisa dibaca file lain
extern bool isDirty;
extern char buffer[1000];
extern char namaFileDefault[];

// Daftar fungsi buatanmu
void JalankanFiturNew();

#endif