void MenuLogin();

#define Nmaks 100

void gotoxy(int x, int y);
void FullScreen();
void PrintFile (char file [], int x, int y);
void DesainUtama();
void KotakLogin();
void SetColor(unsigned short color);
void FillScreen(int x1, int x2, int y1, int y2, unsigned short color);
void Tanggal ();
void Waktu ();


void gotoxy(int x, int y)													//Fungsi untuk tata letak program, seperti titik koordinat
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void FullScreen()															//Fungsi untuk layar penuh
{
	//////////////////SetColor(69);
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}


void PrintFile (char file [], int x, int y)									//Fungsi untuk mencetak File TXT, atau notepad
{
	//DECLARATION
	FILE *TXTFile;
	char Data[Nmaks];
	
	//ALGORITM
	if ((TXTFile = fopen (file , "r")) == NULL ) 
	{
		puts ("Tidak bisa membuka file ");
	}
	while (fgets (Data, Nmaks, TXTFile ))
	{
		gotoxy(x,y);
		printf("%s", Data);
		y++;
	}
	fclose (TXTFile);
}

void KotakLogin()
{
	int i;
	for(i=23;i<=33;i++)
	{
		gotoxy(73,i),	printf("%c%c",178,178); //garis pinggir kiri menu login 
		gotoxy(122,i),	printf("%c%c",178,178);
	}
	for(i=73;i<=122;i++)
	{
		gotoxy(i,23),	printf("%c%c",178,178); //garis pinggir kanan menu login
		gotoxy(i,33),	printf("%c%c",178,178);
	}
	for(i=77;i<=119;i++)
	{
		gotoxy(i,26), 	printf("%c",205);
		gotoxy(i,28), 	printf("%c",205);
		gotoxy(i,30),	printf("%c",205);
	}
	//pinggir atas
	gotoxy(76,26), 	printf("%c", 167);
	gotoxy(120,26),	printf("%c", 167);
	
	//pinggir bawah
	gotoxy(76,30), 	printf("%c", 167);
	gotoxy(120,30), printf("%c", 167);
	
	//samping
	gotoxy(76,27), 	printf("%c", 167);
	gotoxy(120,27), printf("%c", 167);
	gotoxy(76,28), 	printf("%c", 167);
	gotoxy(120,28), printf("%c", 167);
	gotoxy(76,29), 	printf("%c", 167);
	gotoxy(120,29), printf("%c", 167);	
	
}
	
void SetColor(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,color);
}


void FillScreen(int x1, int x2, int y1, int y2, unsigned short color)
{
	int i,j,x,y;
	x = x1;
	y = y1;
	SetColor(color);
	system("color F0");
	while(y<=y2)
	{
		x = x1;
		gotoxy(x,y);
		while(x<=x2)
		{
			printf(" ");
			x++;
		}
		y++;
	}
}

void Tanggal ()
{
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	printf("%02d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}
void Waktu ()
{
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
	printf("%02d:%02d", tm.tm_hour, tm.tm_min);
}
