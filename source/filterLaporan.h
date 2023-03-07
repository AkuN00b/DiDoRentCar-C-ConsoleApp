//Pembuatan Laporan
void SortingRiwayatBulanan();
void SortingRiwayatTahunan();
void TampilRiwayatSort();

struct lapPenyewaan
{
    int kodePenyewaan;
    int idMobil;
    int idSupir;
    int idUser;
    char namaMobil[50];
    char namaSupir[50];
    char namaUser[50];
    char sim[20];
    char nik[20];
    char alamatTempatTinggal[50];
    int umur;
    int jumlahHari;
    int harga;
    int hargaBayar;
    int hargaKembali;
    int tgl;
    int bulan;
    int tahun;
    char status[50];
};

struct lapPenyewaan lapPnyw;

void SortingRiwayatBulanan ()
{
	int cekbulan;
	int cektahun;
	FILE  *Riwayat;
	FILE  *TempRiwayat;
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	int fixCol = 36;

	gotoxy (fixCol,22);	printf ("[1]  Januari ");
	gotoxy (fixCol,23);	printf ("[2]  Februari ");
	gotoxy (fixCol,24);	printf ("[3]  Maret ");
	gotoxy (fixCol,25);	printf ("[4]  April ");
	gotoxy (fixCol,26);	printf ("[5]  Mei ");
	gotoxy (fixCol,27);	printf ("[6]  Juni ");
	gotoxy (fixCol,28);	printf ("[7]  Juli ");
	gotoxy (fixCol,29);	printf ("[8]  Agustus ");
	gotoxy (fixCol,30);	printf ("[9]  September ");
	gotoxy (fixCol,31);	printf ("[10] Oktober ");
	gotoxy (fixCol,32);	printf ("[11] November ");
	gotoxy (fixCol,33);	printf ("[12] Desember ");

	monthyear();
	gotoxy (41,17);printf ("Masukan No Bulan : ");
	gotoxy (61,17);getnum (&cekbulan,2);
	gotoxy (41,19);printf ("Masukan Tahun    : ");
	gotoxy (61,19);getnum(&cektahun,4);

	Riwayat = fopen ("database/customer/transaksi.dat","rb");
	TempRiwayat = fopen ("database/customer/tempTransaksiLaporan.dat","wb");

	fread (&lapPnyw,sizeof (lapPnyw),1,Riwayat);
	while (!feof(Riwayat))
	{
		if((cekbulan == lapPnyw.bulan) && (cektahun == lapPnyw.tahun))
		{
			fwrite(&lapPnyw,sizeof(lapPnyw),1,TempRiwayat);
		}
		fread (&lapPnyw, sizeof(lapPnyw),1,Riwayat);
	}

	fclose (Riwayat);
	fclose (TempRiwayat);
	BersihKanan();
	TampilRiwayatSort ();
}

void SortingRiwayatTahunan ()
{
	int cektahun;
	FILE  *Riwayat;
	FILE  *TempRiwayat;
	OutterBorder();

	year();
	gotoxy (41,19);printf ("Masukan Tahun    : ");
	gotoxy (61,19);getnum(&cektahun,4);

	Riwayat = fopen ("database/customer/transaksi.dat","rb");
	TempRiwayat = fopen ("database/customer/tempTransaksiLaporan.dat","wb");

	fread (&lapPnyw,sizeof (lapPnyw),1,Riwayat);
	while (!feof(Riwayat))
	{
		if(cektahun == lapPnyw.tahun)
		{
			fwrite(&lapPnyw,sizeof(lapPnyw),1,TempRiwayat);
		}
		fread (&lapPnyw, sizeof(lapPnyw),1,Riwayat);
	}
	fclose (Riwayat);
	fclose (TempRiwayat);
	BersihKanan();
	TampilRiwayatSort ();
}

void TampilRiwayatSort ()
{
	int i;
	int y, row;
	y=19;
	char harga [25];

	OutterBorder();
	BersihKanan();
	BersihKiri();

	FILE *Riwayat;
	FILE *TempRiwayat;
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	int total=0;

	TempRiwayat = fopen ("database/customer/tempTransaksiLaporan.dat","rb");

	gotoxy(43,15);
    printf("Kode");

    gotoxy(60,15);
    printf("Tanggal");

    gotoxy(85,15);
    printf("Nama Supir");

    gotoxy(99,15);
    printf("Nama User");

    gotoxy(112,15);
    printf("Nama User");

    gotoxy(125,15);
    printf("Status");

    gotoxy(145,15);
    printf("Harga");

    gotoxy(41,16);
    printf("===================================================================================================================");

    row = 17;

	fread (&lapPnyw,sizeof (lapPnyw),1,TempRiwayat);
	while (!feof (TempRiwayat))
	{
        gotoxy (43,row);
        printf("PNYW%d",lapPnyw.kodePenyewaan); fflush(stdin);

        gotoxy (60,row);
        printf("%d-%d-%d", lapPnyw.tgl,lapPnyw.bulan,lapPnyw.tahun); fflush(stdin);

        gotoxy (85,row);
        printf("%s",lapPnyw.namaMobil); fflush(stdin);

        gotoxy (99,row);
        printf("%s",lapPnyw.namaSupir); fflush(stdin);

        gotoxy (112,row);
        printf("%s",lapPnyw.namaUser); fflush(stdin);

        gotoxy (125,row);
        printf("%s",lapPnyw.status); fflush(stdin);

        rupiah(lapPnyw.harga,harga);
        gotoxy (145,row);
        printf("Rp %s",harga); fflush(stdin);

        row++;

		total = total + lapPnyw.harga;

		fread (&lapPnyw,sizeof (lapPnyw),1,TempRiwayat);
	}

	rupiah(total, harga);
	gotoxy(135,row+3),printf("Total = Rp %s", harga);

	while (feof (TempRiwayat))
	{
		break;
	}

	fclose(TempRiwayat);
	getch();
	system("cls");
	ManagerMainMenu ();
}
