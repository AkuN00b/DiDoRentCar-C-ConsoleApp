#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "Gotoxy.h"
#include "CRUDBARANG.h"
#include "CRUDKASIR.h"
#include "MenuADMIN.h"
#include "LOGIN.h"
#include "MenuUTAMA.h"



main () 
{
	int i;
	
	FullScreen();
	gotoxy(100,20); printf("1.\xc9   2. \xcd     3. \xba     4. \xbb      5. \xc8      6.  \xbc");
	for (i=1; i<=167; i++)
	{
		if (i % 5 == 0)
		{
			gotoxy(i,2); printf("%d", i);
		}
	}
	for (i=1; i<=45; i++)
	{
		if (i % 5 == 0)
		{
			gotoxy(2,i); printf("%d", i);
		}
	}
	getch();
	Menu();
}
