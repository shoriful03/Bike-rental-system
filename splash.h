#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

void Splash_Screen() // Display splash screen.
{
    FILE*ascii= fopen("ascii.txt", "r");
    char c;
    if (ascii == NULL) {
        printf("Failed to open ascii artsaL file.\n");
        return;
    }

    while ((c = fgetc(ascii)) != EOF) {
        putchar(c);
    }

    fclose(ascii);
    sleep(4);   // Display the splash screen for 4 seconds.
    system("cls");    // Clear the screen.

}

