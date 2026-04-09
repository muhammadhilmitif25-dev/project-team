#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include <conio.h>

int main()
{

    Buffer b;
    system("cls"); // Windows
    initBuffer(&b);

    while (1)
    {
        int c = getch();

        // 1. 🔥 ESC (Udah bener punya lu)
        if (c == 27)
        {
            if (b.isSaved == 0)
            {
                printf("\nBelum disave! Keluar? (y/n): ");
                char pilih = getch();
                if (pilih == 'y' || pilih == 'Y')
                    break;
            }
            else
            {
                break;
            }
        }

        // 2. 🔥 ARROW KEY (Tetep kayak kode lu sebelumnya)
        else if (c == 224)
        {
            int arrow = getch();
            if (arrow == 75)
                movekiri(&b);
            else if (arrow == 77)
                movekanan(&b);
            else if (arrow == 72)
                moveatas(&b);
            else if (arrow == 80)
                movebawah(&b);
        }

        // 3. 🔥 BACKSPACE
        else if (c == 8)
        {
            deleteChar(&b);
        }

        // 4. 🔥 ENTER
        else if (c == 13)
        {
            newLine(&b);
        }

        // 5. 🔥 KARAKTER BIASA (NAH, TAMBAHIN FILTERNYA DI SINI)
        // Supaya karakter aneh/tombol fungsi nggak masuk ke insertChar
 
        else if (c >= 32 && c <= 126)
        {
            insertChar(&b, (char)c);
        }

        // --- REFRESH DISPLAY ---
        system("cls");
        displayBuffer(&b);
    }
}