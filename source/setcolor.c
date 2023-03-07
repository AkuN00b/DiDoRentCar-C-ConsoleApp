#include <stdio.h>
#include <windows.h>
#include <time.h>

void SetColor(unsigned short color)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleOutput,color);
}

main()
{
	int i;
//	for (i=1; i<=500; i++)
//	{
//		SetColor(i);
//		printf("warna ke %i ",i);
//		printf("\n");
//	}
//	
//	for(i=1; i<=300; i++)
//	{
//		printf("%c",i);
//		printf("garis ke %i",i);
//		printf("\n");
//	}
	
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	printf("now: %d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}
