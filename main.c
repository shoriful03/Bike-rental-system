#include <stdio.h>
#include <stdlib.h>
#include "splash.h"
#include "login.h"
#include "menu.h"

int main() {
    Splash_Screen();
    login();
    mainMenu();
    return 0;
}
