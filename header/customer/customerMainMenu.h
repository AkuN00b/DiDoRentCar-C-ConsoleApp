#ifndef customerMainMenu

/* ********* CUSTOMER ********* */
/* ********* MAIN MENU ********* */

bool found;

struct trsPenyewaan
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

struct trsPenyewaan pnyw;

struct trsMobil
{
    int No;
	char Tipe[25];
	int Harga;
	char Kapasitas[50];
	char Status[25];
};

struct trsMobil mbl;

struct dataMobil
{
    int No;
	char Tipe[25];
	int Harga;
	char Kapasitas[50];
	char Status[25];
};

struct dataMobil datambl;
struct dataMobil validasiMbl;

struct trsSupir
{
    int No;
    char namaLengkap[50];
    int harga;
    char phone[50];
    char status[50];
};

struct trsSupir spr;

struct dataSupir
{
    int No;
    char namaLengkap[50];
    int harga;
    char phone[50];
    char status[50];
};

struct dataSupir dataspr;
struct dataSupir validasiSpr;
struct dataSupir cekTotalSpr;

struct trsUser
{
    int No;
    char namaLengkap[50];
    char password[50];
    char phone[50];
    char role[50];
};

struct trsUser usr;

void CustomerMainMenu()
{
    system("cls");
    int choose;

    OutterBorder();
	BersihKanan();
	BersihKiri();

    gotoxy(4,14);printf("Menu Customer");
    gotoxy(4,15);printf("Pilih Opsi: ");

    gotoxy(4,16);printf("1. Penyewaan Mobil");
    gotoxy(4,17);printf("2. Riwayat Penyewaan");
    gotoxy(4,18);printf("99. Logout");

    gotoxy(4,19);printf("Pilihan Opsi: ");
    scanf("%i", &choose);

    switch(choose)
    {
        case 1:
            penyewaanMobil();
            break;

        case 2:
            riwayatPenyewaan();
            break;

        case 99:
            customerLogout();
            break;

        default:
            gotoxy(60,33); printf("Angka tidak sesuai, tekan untuk melanjutkan....\n");
            getch();

            CustomerMainMenu();
    }
}

void penyewaanMobil()
{
    gotoxy(43,13); printf("Penyewaan Mobil");

    int acc, harga, hargaKembali, id, row, idMobil, idSupir;
    char hargaRp[20], hargaMobil[20], hargaSupir[20];

    FILE *arsUser;
	FILE *baru;
	FILE *cekId, *loginSessionUser, *ek, *fk;

	FILE *transaksi;

    transaksi = fopen("database/customer/transaksi.dat", "ab");

    cekId = fopen("database/customer/transaksi.dat", "rb");

    fread(&pnyw, sizeof(pnyw), 1, cekId);
    while(!feof(cekId))
    {
        fread(&pnyw, sizeof(pnyw), 1, cekId);
        id = pnyw.kodePenyewaan;
    }

    fclose(cekId);
    pnyw.kodePenyewaan= id + 1;
    
    gotoxy(43,15); printf("Kode penyewaan %d\n\n", pnyw.kodePenyewaan);

    arsUser = fopen("database/users.dat", "rb");
    baru = fopen("database/trsUsers.dat", "wb");
    loginSessionUser = fopen("database/customerLoginSession.dat", "rb");

    SYSTEMTIME str_t;
	GetSystemTime(&str_t);

    harga = 0;

    /* ==================== DATA USER ====================== */

    fread(&usr, sizeof(usr), 1, loginSessionUser);
    gotoxy(43,20);	printf("-----Data Berhasil Ditemukan-----");
    gotoxy(43,22);	printf("ID: USR%i ",usr.No);
    gotoxy(43,23);	printf("Nama Lengkap\t: %s",usr.namaLengkap);
    gotoxy(43,24);	printf("Password\t\t: %s",usr.password);
    gotoxy(43,25);	printf("No Telp\t\t: %s",usr.phone);
    gotoxy(43,26);	printf("Role\t\t: %s",usr.role);

    pnyw.idUser = usr.No;

    fwrite(&usr,sizeof(usr),1,baru);
    strcpy(pnyw.namaUser,usr.namaLengkap);
    fread(&usr, sizeof(usr), 1, loginSessionUser);

    fclose(arsUser);
    fclose(baru);
    fclose(loginSessionUser);

    getch();

    /* ==================== DATA USER ====================== */

    /* ==================== VALIDASI KETERSEDIAAN SUPIR ====================== */

    int isTersedia;

    isTersedia = 0;
    ans = 'Y';

    fk = fopen("database/supir.dat", "rb");
    ek = fopen("databse/tempSupir.dat", "wb");

    fread(&cekTotalSpr, sizeof(cekTotalSpr),1,fk);
    while (!feof(fk))
    {
        if (!strcmp(cekTotalSpr.status, "Tersedia"))
        {
            isTersedia = 1;
            fread(&cekTotalSpr, sizeof(cekTotalSpr),1,fk);
        }
        else
        {
            fwrite(&cekTotalSpr,sizeof(cekTotalSpr),1,ek);
            fread(&cekTotalSpr, sizeof(cekTotalSpr),1,fk);
        }
    }

    if (isTersedia == 0)
    {
        OutterBorder();
        BersihKanan();
        BersihKiri();

        gotoxy(43,16); printf("Konfirmasi, ketersediaan supir tidak ada, apakah ingin melanjutkan? [y/n] -> ");
        scanf(" %c", &ans);
        fflush(stdin);
    }

    if (toupper(ans) == 'N')
    {
        CustomerMainMenu();
    }

    fclose(fk);
    fclose(ek);

    /* ==================== VALIDASI KETERSEDIAAN SUPIR ====================== */

    /* ==================== DATA MOBIL ====================== */

    char status[50];

    inputMobil:

	OutterBorder();
	BersihKanan();
	BersihKiri();

	FILE *arsMobil;
	FILE *baruMobil;

    ek = fopen("database/admin/mobilRecord.dat", "rb");
    fk = fopen("database/admin/tempMobil.dat", "wb");

    arsMobil = fopen("database/admin/mobilRecord.dat", "rb");
    baruMobil = fopen("database/trsMobilRecord.dat", "wb");

    gotoxy(43,16);
    printf("No");

    gotoxy(53,16);
    printf("Tipe");

    gotoxy(75,16);
    printf("Harga");

    gotoxy(98,16);
    printf("Kapasitas");

    gotoxy(113,16);
    printf("Status\n");

    gotoxy(41,17);
    printf("===================================================================================================================");

    row = 18;

    found = false;
    fread(&datambl, sizeof(datambl),1,ek);
    while (!feof(ek))
    {
        if (!strcmp(datambl.Status, "Tersedia"))
        {
            gotoxy(43,row);
            printf("CAR%d ",datambl.No); fflush(stdin);

            gotoxy(53,row);
            printf("%s", datambl.Tipe); fflush(stdin);

            rupiah(datambl.Harga, hargaMobil);
            gotoxy(75,row);
            printf("Rp. %s", hargaMobil); fflush(stdin);

            gotoxy(98,row);
            printf("%s", datambl.Kapasitas); fflush(stdin);

            gotoxy(113,row);
            printf("%s", datambl.Status); fflush(stdin);
            row++;

            fread(&datambl, sizeof(datambl),1,ek);
        }
        else
        {
            fwrite(&datambl,sizeof(datambl),1,fk);
            fread(&datambl,sizeof(datambl),1,ek);
        }
    }
    fclose(ek);
    fclose(fk);

    getch();

    OutterBorder();
	BersihKanan();
	BersihKiri();

    gotoxy(43,40); printf("Tekan 0 untuk membatalkan");
    gotoxy(43,17); printf("Data Mobil");
	gotoxy(43,18); printf("ID Mobil: CAR"); fflush(stdin); getnum(&pnyw.idMobil,4);

    if(pnyw.idMobil == 0)
    {
        CustomerMainMenu();
    }

    strcpy(status, "Tersedia");

	found = false;
	fread(&mbl,sizeof(mbl),1,arsMobil);
	while((!found)&&(!feof(arsMobil)))
	{
        if (mbl.No == pnyw.idMobil && (!strcmp(mbl.Status, status)))
        {
            found = true;
        }
        else
        {
            fwrite(&mbl,sizeof(mbl),1,baruMobil);
            fread(&mbl,sizeof(mbl),1,arsMobil);
        }
	}

	if(found == true)
	{
		gotoxy(43,20);	printf("-----Data Berhasil Ditemukan-----");
		gotoxy(43,22);	printf("ID: CAR%i ",mbl.No);
		gotoxy(43,23);	printf("Tipe\t: %s",mbl.Tipe);
		gotoxy(43,24);	printf("Harga\t\t: %d",mbl.Harga);
		gotoxy(43,25);	printf("Kapasitas\t\t: %s",mbl.Kapasitas);
		gotoxy(43,26);	printf("Status\t\t: %s",mbl.Status);

		harga = mbl.Harga;

        idMobil = mbl.No;

		strcpy(pnyw.namaMobil,mbl.Tipe);
	}
	else
	{
		MessageBox(NULL, "Mobil Belum Tersedia"," ATTENTION ",MB_OK);
		goto inputMobil;
	}

	getch();

	/* ==================== DATA MOBIL ====================== */

	/* ==================== DATA SUPIR ====================== */

	int useSupir;

    if (isTersedia == 1)
    {
        OutterBorder();
        BersihKanan();
        BersihKiri();

        gotoxy(43,17); printf ("Pakai supir (Y/N)");
        fflush(stdin); acc = getch();

        inputSupir:

        OutterBorder();
        BersihKanan();
        BersihKiri();

        fk = fopen("database/supir.dat", "rb");
        ek = fopen("databse/tempSupir.dat", "wb");

        if (acc == 'Y' || acc == 'y')
        {
            gotoxy(43,18);
            printf("No");

            gotoxy(53,18);
            printf("Nama Lengkap");

            gotoxy(75,18);
            printf("Harga");

            gotoxy(98,18);
            printf("Phone");

            gotoxy(123,18);
            printf("Status");

            gotoxy(41,19);
            printf("===================================================================================================================");

            row = 20;

            fread(&dataspr, sizeof(dataspr),1,fk);
            while (!feof(fk))
            {
                if (!strcmp(dataspr.status, "Tersedia"))
                {
                    gotoxy(43,row);
                    printf("SPR%d",dataspr.No); fflush(stdin);

                    gotoxy(53,row);
                    printf("%s",dataspr.namaLengkap); fflush(stdin);

                    rupiah(dataspr.harga, hargaSupir);
                    gotoxy(75,row);
                    printf("Rp. %s", hargaSupir); fflush(stdin);

                    gotoxy(98,row);
                    printf("%s", dataspr.phone); fflush(stdin);

                    gotoxy(123,row);
                    printf("%s", dataspr.status); fflush(stdin);
                    row++;

                    fread(&dataspr, sizeof(dataspr),1,fk);
                }
                else
                {
                    fwrite(&dataspr,sizeof(dataspr),1,ek);
                    fread(&dataspr,sizeof(dataspr),1,fk);
                }
            }
            fclose(fk);
            fclose(ek);

            getch();

            OutterBorder();
            BersihKanan();
            BersihKiri();

            FILE *arsSupir;
            FILE *baruSupir;

            arsSupir = fopen("database/supir.dat", "rb");
            baruSupir = fopen("database/trsSupir.dat", "wb");

            gotoxy(43,19); printf("Data Supir");
            gotoxy(43,20); printf("ID Supir: SPR"); fflush(stdin); getnum(&pnyw.idSupir,4);

            found = false;
            fread(&spr,sizeof(spr),1,arsSupir);
            while((!found)&&(!feof(arsSupir)))
            {
                if (spr.No == pnyw.idSupir && (!strcmp(spr.status, status)))
                {
                    found = true;
                }
                else
                {
                    fwrite(&spr,sizeof(spr),1,baruSupir);
                    fread(&spr,sizeof(spr),1,arsSupir);
                }

            }

            if(found == true)
            {
                gotoxy(43,21);	printf("-----Data Berhasil Ditemukan-----");
                gotoxy(43,23);	printf("ID: SPR%i ",spr.No);
                gotoxy(43,24);	printf("Tipe\t: %s",spr.namaLengkap);
                gotoxy(43,25);	printf("Harga\t\t: %d",spr.harga);
                gotoxy(43,26);	printf("Kapasitas\t\t: %s",spr.phone);
                gotoxy(43,27);	printf("Status\t\t: %s",spr.status);

                harga = harga + spr.harga;

                idSupir = spr.No;

                strcpy(pnyw.namaSupir,spr.namaLengkap);
            }
            else
            {
                MessageBox(NULL, "Supir Belum Tersedia"," ATTENTION ",MB_OK);
                goto inputSupir;
            }

            useSupir = 1;

            getch();
        } else
        {
            strcpy(pnyw.namaSupir, "Tidak Ada Supir");
        }
    } else
    {
        strcpy(pnyw.namaSupir, "Tidak Ada Supir");
    }


    /* ==================== DATA SUPIR ====================== */

    /* ==================== DATA DETAIL PELANGGAN ====================== */

    OutterBorder();
	BersihKanan();
	BersihKiri();

    gotoxy(43,17); printf("SIM: "); fflush(stdin); getteks(pnyw.sim,20);
    gotoxy(43,18); printf("NIK: "); fflush(stdin); getteks(pnyw.nik,20);
    gotoxy(43,19); printf("Alamat Tempat Tinggal: ");
    fflush(stdin);
    getteks(pnyw.alamatTempatTinggal, 50);

    gotoxy(43,20); printf("Umur: "); fflush(stdin); getnum(&pnyw.umur,2);
    gotoxy(43,21); printf("Lama Penyewaan: "); fflush(stdin); getnum(&pnyw.jumlahHari,2);

    harga = harga * pnyw.jumlahHari;
    gotoxy(43,22); printf("Total Harga: %d", harga);
    pnyw.harga = harga;

    BayarHarga:
    gotoxy(43,23); printf("Bayar Harga: ");
    fflush(stdin);
    getRp(&pnyw.hargaBayar, 1, 20, 57, 23);

    if (harga <= pnyw.hargaBayar)
    {

    } else
    {
        MessageBox(NULL, "Uang tidak mencukupi, silahkan input ulang"," ATTENTION ",MB_OK);
        goto BayarHarga;
    }

    hargaKembali = pnyw.hargaBayar - pnyw.harga;
    gotoxy(43,24); printf("Harga Kembali: %d", hargaKembali);

    pnyw.tgl = str_t.wDay;
    pnyw.bulan = str_t.wMonth;
    pnyw.tahun = str_t.wYear;

    pnyw.hargaKembali = hargaKembali;

    /* ==================== VALIDASI STATUS MOBIL ====================== */

    FILE *bacaDataMobil, *tulisDataMobil;
	char tidakTersedia[50];

	found = false;

	strcpy(tidakTersedia, "Tidak Tersedia");

	bacaDataMobil = fopen("database/admin/mobilRecord.dat", "rb");
	tulisDataMobil = fopen("database/admin/mobilRecordTemp.dat", "wb");

	fread (&validasiMbl, sizeof(validasiMbl), 1, bacaDataMobil);
    while(!feof(bacaDataMobil))
    {
        if (validasiMbl.No == idMobil)
        {
            strcpy(validasiMbl.Status, tidakTersedia);
            fwrite(&validasiMbl, sizeof(validasiMbl), 1, tulisDataMobil);
        } else
        {
            fwrite(&validasiMbl, sizeof(validasiMbl), 1, tulisDataMobil);
        }
        fread (&validasiMbl, sizeof(validasiMbl), 1, bacaDataMobil);
    }
    fclose(bacaDataMobil);
    fclose(tulisDataMobil);

    bacaDataMobil = fopen("database/admin/mobilRecord.dat", "wb");
	tulisDataMobil = fopen("database/admin/mobilRecordTemp.dat", "rb");

    fread(&validasiMbl, sizeof(validasiMbl), 1, tulisDataMobil);
	while(!feof(tulisDataMobil))
    {
        fwrite(&validasiMbl, sizeof(validasiMbl), 1, bacaDataMobil);
        fread(&validasiMbl, sizeof(validasiMbl), 1, tulisDataMobil);
    }

    fclose(bacaDataMobil);
    fclose(tulisDataMobil);

    /* ==================== VALIDASI STATUS MOBIL ====================== */

    /* ==================== VALIDASI STATUS SUPIR ====================== */

    if (useSupir == 1)
    {
        FILE *bacaDataSupir, *tulisDataSupir;
        char tidakTersediaSupir[50];

        found = false;

        strcpy(tidakTersediaSupir, "Tidak Tersedia");

        bacaDataSupir = fopen("database/supir.dat", "rb");
        tulisDataSupir = fopen("database/supirTemp.dat", "wb");

        fread (&validasiSpr, sizeof(validasiSpr), 1, bacaDataSupir);
        while(!feof(bacaDataSupir))
        {
            if (validasiSpr.No == idSupir)
            {
                strcpy(validasiSpr.status, tidakTersediaSupir);
                fwrite(&validasiSpr, sizeof(validasiSpr), 1, tulisDataSupir);
            } else
            {
                fwrite(&validasiSpr, sizeof(validasiSpr), 1, tulisDataSupir);
            }
            fread (&validasiSpr, sizeof(validasiSpr), 1, bacaDataSupir);
        }
        fclose(bacaDataSupir);
        fclose(tulisDataSupir);

        bacaDataSupir = fopen("database/supir.dat", "wb");
        tulisDataSupir = fopen("database/supirTemp.dat", "rb");

        fread(&validasiSpr, sizeof(validasiSpr), 1, tulisDataSupir);
        while(!feof(tulisDataSupir))
        {
            fwrite(&validasiSpr, sizeof(validasiSpr), 1, bacaDataSupir);
            fread(&validasiSpr, sizeof(validasiSpr), 1, tulisDataSupir);
        }

        fclose(bacaDataSupir);
        fclose(tulisDataSupir);
    }

    /* ==================== VALIDASI STATUS SUPIR ====================== */

    strcpy(pnyw.status, "Penyewaan");

    fwrite(&pnyw,sizeof(pnyw),1,transaksi);
    fclose(transaksi);

    /* ==================== DATA DETAIL PELANGGAN ====================== */

    getch();
    CustomerMainMenu();
}

void riwayatPenyewaan()
{
    gotoxy(43,13); printf("Riwayat Penyewaan");

    int row, idUser;
	char hargarp[20], hargarpBayar[20], hargarpKembali[20];
	FILE *loginSessionUser;

	FILE *transaksi;
	transaksi = fopen("database/customer/transaksi.dat", "rb");

	if (transaksi == NULL)
    {
        MessageBox(NULL, "Belum Ada Transaksi"," ATTENTION ",MB_OK);
        CustomerMainMenu();
    }

    gotoxy(43,15);
    printf("Kode");

    gotoxy(53,15);
    printf("Nama Mobil");

    gotoxy(73,15);
    printf("Nama Supir");

    gotoxy(93,15);
    printf("Nama User");

    gotoxy(113,15);
    printf("Total Harga\n");

    gotoxy(41,16);
    printf("===================================================================================================================");

    row = 17;

    loginSessionUser = fopen("database/customerLoginSession.dat", "rb");

    fread(&usr,sizeof(usr),1,loginSessionUser);
	idUser = usr.No;
	fclose(loginSessionUser);

	fread(&pnyw,sizeof(pnyw),1,transaksi);
	while (!feof(transaksi))
	{
	    if (idUser == pnyw.idUser)
        {
            gotoxy(43,row);
            printf("PNYW%d ",pnyw.kodePenyewaan); fflush(stdin);

            gotoxy(53,row);
            printf("%s", pnyw.namaMobil); fflush(stdin);

            gotoxy(73,row);
            printf("%s", pnyw.namaSupir); fflush(stdin);

            gotoxy(93,row);
            printf("%s", pnyw.namaUser); fflush(stdin);

            rupiah(pnyw.harga, hargarp);
            gotoxy(113,row);
            printf("%s", hargarp); fflush(stdin);

            row++;
        }

        fread(&pnyw,sizeof(pnyw),1,transaksi);
	}

    fclose(transaksi);
    getch();
    CustomerMainMenu();
}

/* ********* EXIT SCREEN ********* */

void customerLogout() // function to exit
{
    gotoxy(60,33); printf("Berhasil Logout, tekan untuk melanjutkan...\n");
    getch();

    system("cls");
    LoginForm();
}

#define customerMainMenu
#endif // customerMainMenu
