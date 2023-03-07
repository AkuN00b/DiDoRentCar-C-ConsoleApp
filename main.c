#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

/* ********* LOGIN & SIGNUP ********* */

#include "header/loginSignUp.h"


/* ********* ADMIN ********* */

#include "header/admin/adminMainMenu.h"
#include "header/admin/menu/masterUser.h"
#include "header/admin/menu/masterMobil.h"
#include "header/admin/menu/masterSupir.h"


/* ********* CUSTOMER ********* */

#include "header/customer/customerMainMenu.h"


/* ********* MANAGER ********* */

#include "header/manager/managerMainMenu.h"


/* ********* SOURCE ********* */

#include "source/getlib.h"
#include "source/lib.h"
#include "source/gotoxy.h"
#include "source/bingkai.h"
#include "source/filterLaporan.h"

void fullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

int main()
{
    if (stat("database") == -1)
    {
        mkdir("database");
    }

    fullscreen();
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    system("color EA");

    SelamatDatang();
    WelcomeScreen();
    Createdby();
    getch();
    BersihSemuaLayar();
    LoginForm();
}
