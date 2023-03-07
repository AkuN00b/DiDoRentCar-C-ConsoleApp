#ifndef masterSupir

struct mSupir
{
    int No;
    char namaLengkap[50];
    int harga;
    char phone[50];
    char status[50];
};

struct mSupir ms;

struct mSupirNew {
    int NoBaru;
    int PhoneBaru;
};

struct mSupirNew msn;

int b;
char ans;

void MasterSupirMenu()
{
    system("cls");
    int choose;

    OutterBorder();
	BersihKanan();
	BersihKiri();

    gotoxy(4,14); printf("Menu Admin - Master Supir");
    gotoxy(4,15); printf("Pilih Opsi: \n\n");

    gotoxy(4,16); printf("1. Tambah Supir \n");
    gotoxy(4,17); printf("2. Edit Supir \n");
    gotoxy(4,18); printf("3. Hapus Supir \n");
    gotoxy(4,19); printf("99. Kembali \n");

    LihatSupir();

    gotoxy(4,20); printf("Pilihan Opsi: ");
    scanf("%i", &choose);

    switch(choose)
    {
        case 1:
            TambahSupir();
            break;

        case 2:
            EditSupir();
            break;

        case 3:
            HapusSupir();
            break;

        case 99:
            AdminMainMenu();
            break;

        default:
            MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan"," ATTENTION ",MB_OK);

            MasterSupirMenu();
    }
}

void TambahSupir()
{
    system("cls");

    char ans;
    int id, optStatus;
    FILE *ek, *fk;

    OutterBorder();
	BersihKanan();
	BersihKiri();

	gotoxy(50,40); printf("Tekan 0 untuk membatalkan");

    fk = fopen("database/supir.dat", "ab");
    ek = fopen("database/supir.dat", "rb");

    fread(&ms, sizeof(ms), 1, ek);
    while(!feof(ek))
    {
        fread(&ms, sizeof(ms), 1, ek);
        id = ms.No;
    }

    fclose(ek);

    ms.No = id + 1;

    gotoxy(50,14); printf(" Tambah Supir");

    /* ********* No ********* */
    gotoxy(50,16); printf(" No: SPR%d", ms.No);

    /* ********* Full Name ********* */
    gotoxy(50,17);printf(" Full Name: ");
    fflush(stdin);
    getteks(ms.namaLengkap, 50);

    if (!strcmp(ms.namaLengkap, "0"))
    {
        MasterSupirMenu();
    }

    ms.namaLengkap[0] = toupper(ms.namaLengkap[0]);

    /* ********* Harga ********* */
    gotoxy(50,18);printf(" Harga: Rp. ");
    fflush(stdin);
    getRp(&ms.harga, 1, 20, 62, 18);

    /* ********* Phone ********* */
    gotoxy(50,19);printf(" Phone: ");
    fflush(stdin);
    getteks(ms.phone, 50);

    /* ********* Status ********* */
    masukkanStatusSupir:
    gotoxy(50,21); printf(" [1] Tersedia");
    gotoxy(50,22); printf(" [2] Tidak Tersedia");
    gotoxy(50,23); printf(" Status: ");
    getnum(&optStatus,1);

    if (optStatus == 1)
    {
        strcpy(ms.status, "Tersedia");
    } else if (optStatus == 2)
    {
        strcpy(ms.status, "Tidak Tersedia");
    } else
    {
        MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan"," ATTENTION ",MB_OK);
        getch();
        goto masukkanStatusSupir;
    }

    ek = fopen("database/supir.dat", "ab");
    fwrite(&ms, sizeof(ms),1,ek);
	fclose(ek);

    MessageBox(NULL, "Information Record Successfull"," ATTENTION ",MB_OK);

    getch();
    sd:
    gotoxy(50,26); printf(" Do you want to add more[Y/N]??");
    scanf(" %c", &ans);
    if (toupper(ans) == 'Y')
    {
        TambahSupir();
    } else if (toupper(ans) == 'N')
    {
        MessageBox(NULL, "Thank You"," ATTENTION ",MB_OK);
        MasterSupirMenu();
    } else
    {
        MessageBox(NULL, "Invalid Input"," ATTENTION ",MB_OK);
        goto sd;
    }
}

void LihatSupir()
{
    int row;
    char harga[20];

    FILE *ek;

    ek = fopen("database/supir.dat", "rb");

    gotoxy(43,14); printf("Data Supir");

    if (ek == NULL)
    {

    } else
    {
        gotoxy(43,16);
        printf("No");

        gotoxy(53,16);
        printf("Nama Lengkap");

        gotoxy(75,16);
        printf("Harga");

        gotoxy(98,16);
        printf("Phone");

        gotoxy(123,16);
        printf("Status");

        gotoxy(41,17);
        printf("===================================================================================================================");

        row = 18;

        fread(&ms, sizeof(ms),1,ek);
        while (!feof(ek))
        {
            gotoxy(43,row);
            printf("SPR%d",ms.No); fflush(stdin);

            gotoxy(53,row);
            printf("%s",ms.namaLengkap); fflush(stdin);

            rupiah(ms.harga, harga);
            gotoxy(75,row);
            printf("Rp. %s", harga); fflush(stdin);

            gotoxy(98,row);
            printf("%s", ms.phone); fflush(stdin);

            gotoxy(123,row);
            printf("%s", ms.status); fflush(stdin);
            row++;

            fread(&ms, sizeof(ms),1,ek);
        }
        fclose(ek);
    }
}

void EditSupir()
{
    FILE *ek, *ft;

    int found;
	int a, optStatus;
	char harga[20];

    system("cls");
    OutterBorder();
	BersihKanan();
	BersihKiri();

	gotoxy(50,40); printf("Tekan 0 untuk membatalkan");

	gotoxy(50,14); printf("Edit Mobil");

    ft = fopen("database/supirTemp.dat", "wb");
    ek = fopen("database/supir.dat", "rb");

    if (ek == NULL)
    {
        MessageBox(NULL, "Can not open file !!"," ATTENTION ",MB_OK);
        MasterSupirMenu();
    }

    gotoxy(50,16);
    printf("Masukkan No Supir yang ingin diupdate: SPR");
    getnum(&msn.NoBaru,4);

    if (msn.NoBaru == 0)
    {
        MasterSupirMenu();
    }

    found = 0;

    if (ft == NULL)
    {
        MessageBox(NULL, "Can not open file !!"," ATTENTION ",MB_OK);
        MasterSupirMenu();
    }

    while (found != 1 && !feof(ek))
	{
		fread (&ms, sizeof(ms) , 1 , ek);
		if(ms.No == msn.NoBaru)
		{
			found = 1;
		}
		else
		{
			fwrite (&ms, sizeof (ms),1,ft);
		}
	}

	if(found == 1)
	{
	    gotoxy(50,18); printf("ID Supir = SPR%d \n", ms.No);
		gotoxy(50,19);	printf("Nama Lengkap     = %s \n ", ms.namaLengkap);
		rupiah(ms.harga, harga);
		gotoxy(50,20);	printf("Harga = Rp. %s \n", harga);
		gotoxy(50,21);	printf("Phone = %s \n", ms.phone);
		gotoxy(50,22);	printf("Status  = %s \n", ms.status);

		gotoxy(50,24);	printf("Pilih data yang akan diupdate = \n");
		gotoxy(50,25);	printf("[1] Nama Lengkap \n");
		gotoxy(50,26);	printf("[2] Harga \n");
		gotoxy(50,27);	printf("[3] Phone \n");
		gotoxy(50,28);	printf("[4] Status \n");
		gotoxy(50,29);	printf("[5] Batal \n");
		gotoxy(50,30);	printf("Pilih = ");
		getnum(&a,1);

		if (a == 1)
        {
            gotoxy(50,31); printf("Masukkan Nama Lengkap = "); fflush(stdin);
            getteks(ms.namaLengkap, 50);

			fwrite(&ms,sizeof(ms),1,ft);
			fread(&ms,sizeof(ms),1,ek);

			while(!feof(ek))
			{
				fwrite(&ms,sizeof(ms),1,ft);
				fread(&ms,sizeof(ms),1,ek);
			}
        }else if(a==2)
		{
			gotoxy(50,31);printf("Masukkan Harga Baru Sewa Supir = Rp. "); fflush(stdin); getRp(&ms.harga,1,20,87,31);
			fwrite(&ms,sizeof(ms),1,ft);
			fread(&ms,sizeof(ms),1,ek);

			while(!feof(ek))
			{
				fwrite(&ms,sizeof(ms),1,ft);
				fread(&ms,sizeof(ms),1,ek);
			}
		} else if(a==3)
		{
			gotoxy(50,31); printf("Masukkan Nomor Telepon Baru = "); fflush(stdin);
            getteks(ms.phone, 50);

			fwrite(&ms,sizeof(ms),1,ft);
			fread(&ms,sizeof(ms),1,ek);

			while(!feof(ek))
			{
				fwrite(&ms,sizeof(ms),1,ft);
				fread(&ms,sizeof(ms),1,ek);
			}
		} else if(a==4)
		{
			masukkanStatusSupir:
            gotoxy(50,31); printf("[1] Tersedia");
            gotoxy(50,32); printf("[2] Tidak Tersedia");
            gotoxy(50,33); printf("Status: ");
            getnum(&optStatus,1);

            if (optStatus == 1)
            {
                strcpy(ms.status, "Tersedia");
            } else if (optStatus == 2)
            {
                strcpy(ms.status, "Tidak Tersedia");
            } else
            {
                MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan..."," ATTENTION ",MB_OK);
                goto masukkanStatusSupir;
            }

			fwrite(&ms,sizeof(ms),1,ft);
			fread(&ms,sizeof(ms),1,ek);

			while(!feof(ek))
			{
				fwrite(&ms,sizeof(ms),1,ft);
				fread(&ms,sizeof(ms),1,ek);
			}
		}
		else
		if(a==5)
		{
			system("cls");
			MasterSupirMenu();
		}
		else
		{
		    MessageBox(NULL, "Pilihan tidak tersedia"," ATTENTION ",MB_OK);
			EditSupir();
		}
		fclose(ek);
		fclose(ft);

		ft = fopen("database/supirTemp.dat", "rb");
		ek = fopen("database/supir.dat", "wb");

		fread (&ms, sizeof(ms),1,ft);
		while(!feof(ft))
		{
			fwrite (&ms, sizeof (ms),1,ek);
			fread (&ms, sizeof (ms),1,ft);
		}
		fclose(ek);
		fclose(ft);

		MessageBox(NULL, "Supir berhasil di update"," ATTENTION ",MB_OK);
		getch();

        sd:
		gotoxy(50,38); printf("Do you want to edit more[Y/N]??");
        scanf(" %c", &ans);
        if (toupper(ans) == 'Y')
        {
            EditSupir();
        } else if (toupper(ans) == 'N')
        {
            MessageBox(NULL, "Thank you :) :)"," ATTENTION ",MB_OK);
            MasterSupirMenu();
        } else
        {
            MessageBox(NULL, "Invalid Input"," ATTENTION ",MB_OK);
            goto sd;
        }
	}

	MessageBox(NULL, "Supir tidak tersedia"," ATTENTION ",MB_OK);
	system("cls");

	remove("database/supir.dat");
    rename("database/supirTemp.dat", "database/supir.dat");

	MasterSupirMenu();
}

void HapusSupir()
{
    int found = 0;
    int IDBaru;
    system("cls");

    OutterBorder();
	BersihKanan();
	BersihKiri();

    FILE *ek, *ft;

    ft = fopen("database/supirTemp2.dat", "wb");
    ek = fopen("database/supir.dat", "rb");

    gotoxy(50,40); printf(" Tekan 0 untuk membatalkan");

    gotoxy(50,14); printf(" Hapus Supir");

    gotoxy(50,16);
    printf(" Masukkan ID Supir yang ingin dihapus: SPR");
    getnum(&IDBaru,4);

    if (IDBaru == 0)
    {
        MasterSupirMenu();
    }

    fread (&ms, sizeof(ms),1,ek);
	while (found != 1 && !feof(ek))
	{
		if (ms.No == IDBaru)
		{
			found = 1;
			break;
		}else
		{
			fwrite (&ms, sizeof (ms),1,ft);
			fread (&ms, sizeof(ms),1,ek);
		}
	}

	if (found == 1)
	{
		fread (&ms, sizeof(ms),1,ek);
		while (!feof(ek))
		{
			fwrite (&ms, sizeof (ms),1,ft);
			fread (&ms, sizeof(ms),1,ek);
		}
	}
	else
	{
	    MessageBox(NULL, "Supir Belum Tersedia"," ATTENTION ",MB_OK);
		MasterSupirMenu();
	}
	fclose(ft);
	fclose(ek);

	ek = fopen("database/supir.dat", "wb");
	ft = fopen("database/supirTemp2.dat", "rb");

	fread (&ms, sizeof(ms),1,ft);
	while(!feof(ft))
	{
		fwrite (&ms, sizeof (ms),1,ek);
		fread (&ms, sizeof(ms),1,ft);
	}
	fclose(ek);
	fclose(ft);

	MessageBox(NULL, "Supir Berhasil Dihapus"," ATTENTION ",MB_OK);
	system("cls");

	remove("database/supir.dat");
    rename("database/supirTemp2.dat", "database/supir.dat");

	MasterSupirMenu();
}

#define masterSupir
#endif // masterSupir


