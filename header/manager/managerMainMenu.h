#ifndef managerMainMenu

struct carLaporan
{
    int No;
	char Tipe[25];
	int Harga;
	char Kapasitas[50];
	char Status[25];
};

struct carLaporan cl;

struct mSupirLaporan
{
    int No;
    char namaLengkap[50];
    int harga;
    char phone[50];
    char status[50];
};

struct mSupir msl;

/* ********* MANAGER ********* */
/* ********* MAIN MENU ********* */

void ManagerMainMenu()
{
    system("cls");
    int choose;

    OutterBorder();
	BersihKanan();
	BersihKiri();

    gotoxy(4,14); printf("Menu Manager");
    gotoxy(4,15); printf("Pilih Opsi: \n");

    gotoxy(4,16); printf("1. Laporan Mobil \n");
    gotoxy(4,17); printf("2. Laporan Supir \n");
    gotoxy(4,18); printf("3. Laporan User \n");
    gotoxy(4,19); printf("4. Laporan PerBulan \n");
    gotoxy(4,20); printf("5. Laporan PerTahun \n");
    gotoxy(4,21); printf("99. Logout \n");

    gotoxy(4,22); printf("Pilihan Opsi: ");
    scanf("%i", &choose);

    switch(choose)
    {
        case 1:
            laporanMobil();
            break;

        case 2:
            laporanSupir();
            break;

        case 3:
            laporanUser();
            break;

        case 4:
            laporanPerBulan();
            break;

        case 5:
            laporanPerTahun();
            break;

        case 99:
            managerLogout();
            break;

        default:
            gotoxy(60,33); printf("Angka tidak sesuai, tekan untuk melanjutkan....\n");
            getch();

            ManagerMainMenu();
    }
}

void laporanMobil()
{
    int row;
    char harga[20];

    FILE *ek;

    system("cls");

    OutterBorder();
	BersihKanan();
	BersihKiri();

    ek = fopen("database/admin/mobilRecord.dat", "rb");

    gotoxy(43,15);
    printf("No");

    gotoxy(53,15);
    printf("Tipe");

    gotoxy(75,15);
    printf("Harga");

    gotoxy(88,15);
    printf("Kapasitas");

    gotoxy(103,15);
    printf("Status\n");

    gotoxy(41,16);
    printf("===================================================================================================================");

    row = 17;

    fread(&cl, sizeof(cl),1,ek);
	while (!feof(ek))
	{
	    gotoxy(43,row);
	    printf("Car%d ",cl.No); fflush(stdin);

        gotoxy(53,row);
        printf("%s", cl.Tipe); fflush(stdin);

        rupiah(cl.Harga, harga);
        gotoxy(75,row);
        printf("%s", harga); fflush(stdin);

        gotoxy(88,row);
        printf("%s", cl.Kapasitas); fflush(stdin);

        gotoxy(103,row);
        printf("%s", cl.Status); fflush(stdin);
        row++;

		fread(&cl, sizeof(cl),1,ek);
	}
	fclose(ek);

    getch();

    system("cls");
    ManagerMainMenu();
}

void laporanSupir()
{
    int row;
    char harga[20];

    FILE *ek;

    system("cls");

    OutterBorder();
	BersihKanan();
	BersihKiri();

    ek = fopen("database/supir.dat", "rb");

    if (ek == NULL)
    {

    } else
    {
        gotoxy(43,15);
        printf("No");

        gotoxy(53,15);
        printf("Nama Lengkap");

        gotoxy(75,15);
        printf("Harga");

        gotoxy(88,15);
        printf("Phone");

        gotoxy(103,15);
        printf("Status\n");

        gotoxy(41,16);
        printf("===================================================================================================================");

        row = 17;

        fread(&ms, sizeof(ms),1,ek);
        while (!feof(ek))
        {
            gotoxy(43,row);
            printf("SPR%d",ms.No); fflush(stdin);

            gotoxy(53,row);
            printf("%s",ms.namaLengkap); fflush(stdin);

            rupiah(ms.harga, harga);
            gotoxy(75,row);
            printf("%s", harga); fflush(stdin);

            gotoxy(88,row);
            printf("%s", ms.phone); fflush(stdin);

            gotoxy(103,row);
            printf("%s", ms.status); fflush(stdin);
            row++;

            fread(&ms, sizeof(ms),1,ek);
        }
        fclose(ek);
    }

    getch();

    system("cls");
    ManagerMainMenu();
}

void laporanUser()
{
    int row;

    system("cls");

    OutterBorder();
	BersihKanan();
	BersihKiri();

    FILE *ek;

    ek = fopen("database/users.dat", "rb");

    gotoxy(43,15);
    printf("No");

    gotoxy(53,15);
    printf("Nama Lengkap");

    gotoxy(75,15);
    printf("Password");

    gotoxy(88,15);
    printf("Phone");

    gotoxy(103,15);
    printf("Role\n");

    gotoxy(41,16);
    printf("===================================================================================================================");

    row = 17;

    fread(&mu, sizeof(mu),1,ek);
	while (!feof(ek))
	{
	    gotoxy(43,row);
	    printf("USR%d",mu.No); fflush(stdin);

	    gotoxy(53,row);
	    printf("%s",mu.namaLengkap); fflush(stdin);

        gotoxy(75,row);
        printf("%s", mu.password); fflush(stdin);

        gotoxy(88,row);
        printf("%s", mu.phone); fflush(stdin);

        gotoxy(103,row);
        printf("%s", mu.role); fflush(stdin);
        row++;

		fread(&mu, sizeof(mu),1,ek);
	}
	fclose(ek);

    getch();

    system("cls");
    ManagerMainMenu();
}

void laporanPerBulan()
{
    system("cls");

    OutterBorder();
	BersihKanan();
	BersihKiri();

    SortingRiwayatBulanan();

    getch();

    system("cls");
    ManagerMainMenu();
}

void laporanPerTahun()
{
    system("cls");

    OutterBorder();
    BersihKanan();
    BersihKiri();

    SortingRiwayatTahunan();

    getch();

    system("cls");
    ManagerMainMenu();
}

/* ********* EXIT SCREEN ********* */

void managerLogout() // function to exit
{
    gotoxy(60,33); printf("Berhasil Logout, tekan untuk melanjutkan...\n");
    getch();

    system("cls");
    LoginForm();
}

#define managerMainMenu
#endif // managerMainMenu
