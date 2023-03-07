void OutterBorder();
void Createdby();
void SelamatDatang();
void MasukProgram();
void BersihSemuaLayar ();
void BersihKanan();
void BersihKiri();


void OutterBorder()
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    gotoxy(10,5); Tanggal ();
    gotoxy(12,7); Waktu ();
    PrintFile("title/title.txt", 58, 4);

	int i, lebar=167, tinggi=11;
	//----------------------------------------------- pojok kiri atas
	gotoxy(0,0);printf("%c",219);
	//----------------------------------------------- garis atas horizon
	for(i=0;i<=lebar;i++)
	{
		gotoxy(i,0);printf("%c",219);
	}

	//----------------------------------------------- garis bawah horizon
	for(i=0;i<=lebar;i++)
	{
		gotoxy(i,12);
		printf("%c",219);
	}

	//----------------------------------------------- garis kiri vertikal
	for(i=1;i<=25;i++)
	{
		gotoxy(0,i);
		printf("%c",219);
	}
	//kotak dalam menu//
	gotoxy(1,13);printf("%c",201);
	gotoxy(1,24);printf("%c",200);

	for (i=14;i<=23;i++)
	{
		gotoxy(1,i);
		printf("%c",186);
	}
	gotoxy(29,13);printf("%c",187);
	gotoxy(29,24);printf("%c",188);

	for (i=14;i<=23;i++)
	{
		gotoxy(29,i);
		printf("%c",186);
	}

	for (i=1;i<=29;i++)
	{
		gotoxy(i,13);
		printf("%c",186);
	}
	for (i=1;i<=29;i++)
	{
		gotoxy(i,24);
		printf("%c",186);
	}
	for(i=26;i<=45;i++)
	{
		gotoxy(0,i);
		printf("%c",219);
	}
	for(i=1;i<=45;i++)
	{
		gotoxy(lebar,i);
		printf("%c",219);
	}

	for (i=1;i<=lebar;i++)
	{
		gotoxy(i,1);
		printf("%c",219);
	}

	//--------------------------------------------buat garis bawah yang menu
	for(i=1;i<=30;i++)
	{
		gotoxy(i,25);
		printf("%c",219);
	}

	gotoxy (2,27);printf("===========================");
	gotoxy (10,29);printf ("CREATED BY");
	gotoxy (2,31);printf("===========================");

	gotoxy (3,35);printf ("ALDI FERDINAND SUPRIYADI");
	gotoxy (8,36);printf ("0320210002");
	gotoxy (3,38);printf ("GERLANDO A. G. CORPUTTY");
	gotoxy (8,39);printf ("0320210027");

	for(i=1;i<=167;i++)
	{
		gotoxy(i,45);
		printf("%c",219);
	}

	/*LOGO */

	for (i=1;i<=45;i++)
	{
		gotoxy (30,i);
		printf("%c",219);
	}

	for (i=26;i<=33;i++) 	//garis kebawah
	{
		gotoxy (30,i);
		printf("%c",219);
	}
}

void SelamatDatang()
{
	//DECLARATION
	int i,j;

	//ALGORITM
	gotoxy(0,0); printf("\xc9");			//sudut siku-siku kiri atas
	for(i=1; i<=166; i++)
	{
		gotoxy(i,0); printf("\xcd");		//garis horizontal
	}
	gotoxy(i,0); printf("\xbb");			//sudut siku-siku kanan atas

	for(j=1; j<=46; j++)
	{
		gotoxy(167,j); printf("\xba");		//garis vertikal
	}

	for(j=1; j<=46; j++)
	{
		gotoxy(0,j); printf("\xba");		//garis vertikal
	}
	gotoxy(0,j); printf("\xc8");			//sudut siku-siku kanan bawah

	for(i=1; i<=166; i++)
	{
		gotoxy(i,j); printf("\xcd");		//garis horizontal
	}
	gotoxy(i,j); printf("\xbc");			//sudut siku-siku kiri bawah

}

void MasukProgram()
{
	//DECLARATION
	int a;
	int b;


	gotoxy(65,18); printf("\xc9");
	for(a=66; a<=100; a++)
	{
		gotoxy(a,18); printf("\xcd");
	}
	gotoxy(a,18); printf("\xbb");

	for(b=19; b<=28; b++)
	{
		gotoxy(101,b); printf("\xba");
	}

	for(b=19; b<=28; b++)
	{
		gotoxy(65,b); printf("\xba");
	}

	gotoxy(65,b); printf("\xc8");
	for(a=66; a<=100; a++)
	{
		gotoxy(a,b); printf("\xcd");
	}
	gotoxy(a,b); printf("\xbc");

	for (a=66; a<=100; a++)
	{
		gotoxy(a,25); printf("\xcd");
	}

}

void Createdby()
{
	//DECLARATION
	int a;
	int b;

	//ALGORITM
	gotoxy(65,34); printf("\xc9");
	for(a=66; a<=101; a++)
	{
		gotoxy(a,34); printf("\xcd");
	}
	gotoxy(a,34); printf("\xbb");

	for(b=35; b<=43; b++)
	{
		gotoxy(102,b); printf("\xba");
	}

	for(b=35; b<=43; b++)
	{
		gotoxy(65,b); printf("\xba");
	}

	gotoxy(65,b); printf("\xc8");
	for(a=66; a<=101; a++)
	{
		gotoxy(a,b); printf("\xcd");
	}
	gotoxy(a,b); printf("\xbc");

	gotoxy(78,37);	printf("Created by : ");
	gotoxy(72,39);	printf("Aldi Ferdinand Supriyadi\n\n");
	gotoxy(68,40);	printf("Gerlando Aryaf Garibaldi Corputty\n");
}

void BersihSemuaLayar ()
{
	//DECLARATION
	int i;
	int j;

	//ALGORITM
	for (i=1; i<= 165; i++)
	{
		for(j=1; j <= 45; j++)
		{
			gotoxy(i,j); printf(" ");
		}
	}
}


void BersihKanan ()
{
	//DECLARATION
	int i;
	int j;

	//ALGORITM
	for(i=31; i<=166; i++)
	{
		for (j=13; j<=44; j++)
		{
			gotoxy(i,j); printf(" ");
		}
	}
}

void BersihKiri ()
{
	//DECLARATION
	int i;
	int j;

	//ALGORITM
	for(i=2; i<=28; i++)
	{
		for (j=14; j<=23; j++)
		{
			gotoxy(i,j); printf(" ");
		}
	}
}

void BersihStruk ()
{
	//DECLARATION
	int i;
	int j;

	//ALGORITM
	for(i=70; i<=150; i++)
	{
		for (j=25; j<=28; j++)
		{
			gotoxy(i,j); printf(" ");
		}
	}
}

