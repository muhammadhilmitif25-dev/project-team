#include <windows.h>
#include <stdbool.h>
#include "kursor.h"

#define ID_NEW 1
HWND hEdit;
extern bool isDirty;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("BUTTON", "New (+)", WS_CHILD | WS_VISIBLE, 10, 50, 1435, 780, hwnd, (HMENU)ID_NEW, NULL, NULL);
            hEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_BORDER, 10, 50, 260, 150, hwnd, NULL, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wp) == ID_NEW) JalankanFitur(hwnd);
            if (HIWORD(wp) == EN_CHANGE) isDirty = true;
            break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR c, int s) {
    WNDCLASS wc = {0};
    wc.lpszClassName = "MinGUI";
    wc.lpfnWndProc = WndProc;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);
    CreateWindow("MinGUI", "Notepad", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 300, 250, NULL, NULL, h, NULL);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}