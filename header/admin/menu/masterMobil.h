#ifndef masterMobil

struct car
{
    int No;
	char Tipe[25];
	int Harga;
	char Kapasitas[50];
	char Status[25];
};

struct car c;

struct carNew {
    int NoBaru;
    int HargaBaru;
};

struct carNew cn;

int b;
char ans;

void MasterMobilMenu()
{
    system("cls");
    int choose;

    OutterBorder();
	BersihKanan();
	BersihKiri();

    LihatMobil();

    gotoxy(4,14); printf("Menu Admin - Master Mobil");
    gotoxy(4,15); printf("Pilih Opsi: \n\n");

    gotoxy(4,16);printf("1. Tambah Mobil \n");
    gotoxy(4,17);printf("2. Edit Mobil \n");
    gotoxy(4,18);printf("3. Hapus Mobil \n");
    gotoxy(4,19);printf("99. Kembali\n");

    gotoxy(4,20);printf("Pilihan Opsi: ");
    scanf("%i", &choose);

    switch(choose)
    {
        case 1:
            TambahMobil();
            break;

        case 2:
            EditMobil();
            break;

        case 3:
            HapusMobil();
            break;

        case 99:
            AdminMainMenu();
            break;

        default:
            MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan"," ATTENTION ",MB_OK);

            MasterMobilMenu();
    }
}

void TambahMobil()
{
    system("cls");

    char ans;
    int id, optTambahMobil, optStatus;
    FILE *ek;

    OutterBorder();
	BersihKanan();
	BersihKiri();

    gotoxy(50,40); printf("Tekan 0 untuk membatalkan");

    ek = fopen("database/admin/mobilRecord.dat", "rb");

    fread(&c, sizeof(c), 1, ek);
    while(!feof(ek))
    {
        fread(&c, sizeof(c), 1, ek);
        id = c.No;
    }

    fclose(ek);
    c.No = id + 1;

    gotoxy(50,14); printf(" Tambah Mobil");

    /* ********* No ********* */
    gotoxy(50,16); printf(" No: CAR%d",c.No);

    /* ********* Tipe ********* */
    gotoxy(50,17);printf(" Tipe: ");
    fflush(stdin);
    getteks(c.Tipe, 25);

    if (!strcmp(c.Tipe, "0"))
    {
        MasterMobilMenu();
    }
    c.Tipe[0] = toupper(c.Tipe[0]);

    /* ********* Harga ********* */
    gotoxy(50,18);printf(" Harga: Rp. ");
    getRp(&c.Harga, 1, 20, 62, 18);

    /* ********* Kapasitas ********* */
    masukkanKapasitasMobil:
    gotoxy(50,20); printf(" [1] Tiga Orang");
    gotoxy(50,21); printf(" [2] Empat Orang");
    gotoxy(50,22); printf(" [3] Lima Orang");
    gotoxy(50,23); printf(" [4] Enam Orang");
    gotoxy(50,24); printf(" Kapasitas: ");
    getnum(&optTambahMobil,1);

    if (optTambahMobil == 1)
    {
        strcpy(c.Kapasitas, "Tiga Orang");
    } else if (optTambahMobil == 2)
    {
        strcpy(c.Kapasitas, "Empat Orang");
    } else if (optTambahMobil == 3)
    {
        strcpy(c.Kapasitas, "Lima Orang");
    } else if (optTambahMobil == 4)
    {
        strcpy(c.Kapasitas, "Enam Orang");
    } else
    {
        MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan"," ATTENTION ",MB_OK);
        goto masukkanKapasitasMobil;
    }

    /* ********* Status ********* */
    masukkanStatusMobil:
    gotoxy(50,26); printf(" [1] Tersedia");
    gotoxy(50,27); printf(" [2] Tidak Tersedia");
    gotoxy(50,28); printf(" Status: ");
    getnum(&optStatus,1);

    if (optStatus == 1)
    {
        strcpy(c.Status, "Tersedia");
    } else if (optStatus == 2)
    {
        strcpy(c.Status, "Tidak Tersedia");
    } else
    {
        MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan"," ATTENTION ",MB_OK);
        goto masukkanStatusMobil;
    }

    ek = fopen("database/admin/mobilRecord.dat", "ab");
    fwrite(&c, sizeof(c),1,ek);
	fclose(ek);

	MessageBox(NULL, "Information Record Successfull"," ATTENTION ",MB_OK);

    getch();
    sd:
    gotoxy(50,31);printf(" Do you want to add more[Y/N]??");
    scanf(" %c", &ans);

    if (toupper(ans) == 'Y')
    {
        TambahMobil();
    } else if (toupper(ans) == 'N')
    {
        MessageBox(NULL, "Thank You"," ATTENTION ",MB_OK);
        MasterMobilMenu();
    } else
    {
        MessageBox(NULL, "Invalid Input"," ATTENTION ",MB_OK);
        goto sd;
    }
}

void LihatMobil()
{
    int row;
    char harga[20];

    FILE *ek;

    gotoxy(43,14); printf("Data Mobil");

    ek = fopen("database/admin/mobilRecord.dat", "rb");

    if (ek == NULL)
    {

    } else
    {
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

        fread(&c, sizeof(c),1,ek);
        while (!feof(ek))
        {
            gotoxy(43,row);
            printf("CAR%d ",c.No); fflush(stdin);

            gotoxy(53,row);
            printf("%s", c.Tipe); fflush(stdin);

            rupiah(c.Harga, harga);
            gotoxy(75,row);
            printf("Rp. %s", harga); fflush(stdin);

            gotoxy(98,row);
            printf("%s", c.Kapasitas); fflush(stdin);

            gotoxy(113,row);
            printf("%s", c.Status); fflush(stdin);
            row++;

            fread(&c, sizeof(c),1,ek);
        }
        fclose(ek);
    }
}

void EditMobil()
{
    FILE *ek, *ft;

    int found;
	int a, optTambahMobil, optStatus;
	char harga[20], ans;

    system("cls");

    OutterBorder();
	BersihKanan();
	BersihKiri();

	gotoxy(50,40); printf("Tekan 0 untuk membatalkan");

	gotoxy(50,14); printf("Edit Mobil");

    ft = fopen("database/admin/mobilRecordTemp.dat", "wb");
    ek = fopen("database/admin/mobilRecord.dat", "rb");

    if (ek == NULL)
    {
        MessageBox(NULL, "Can not open file !!"," ATTENTION ",MB_OK);
        MasterMobilMenu();
    }

    gotoxy(50,16);
    printf("Masukkan ID Car yang ingin diupdate: CAR");
    getnum(&cn.NoBaru,4);

    if (cn.NoBaru == 0)
    {
        MasterMobilMenu();
    }

    found = 0;

    if (ft == NULL)
    {
        MessageBox(NULL, "Can not open file !!"," ATTENTION ",MB_OK);
        MasterMobilMenu();
    }

    while (found != 1 && !feof(ek))
	{
		fread (&c, sizeof(c) , 1 , ek);
		if(c.No == cn.NoBaru)
		{
			found = 1;
		}
		else
		{
			fwrite (&c, sizeof (c),1,ft);
		}
	}

	if(found == 1)
	{
		gotoxy(50,18);	printf("ID Car       = CAR%d \n ", c.No);
		gotoxy(50,19);	printf("Tipe     = %s \n", c.Tipe);
		rupiah(c.Harga, harga);
		gotoxy(50,20);	printf("Harga  = Rp. %s \n", harga);
		gotoxy(50,21);	printf("Kapasitas    = %s \n", c.Kapasitas);
		gotoxy(50,22);	printf("Status     = %s \n", c.Status);

		gotoxy(50,23);	printf("Pilih data yang akan diupdate = \n");
		gotoxy(50,24);	printf("[1] Tipe \n");
		gotoxy(50,25);	printf("[2] Harga \n");
		gotoxy(50,26);	printf("[3] Kapasitas \n");
		gotoxy(50,27);	printf("[4] Status \n");
		gotoxy(50,28);	printf("[5] Keluar \n");
		gotoxy(50,29);	printf("Pilih = ");
		getnum(&a,1);

		if (a == 1)
        {
            gotoxy(50,30);printf("Masukkan Tipe Mobil = ");
            getteks(c.Tipe, 25);
            c.Tipe[0] = toupper(c.Tipe[0]);

			fwrite(&c,sizeof(c),1,ft);
			fread(&c,sizeof(c),1,ek);

			while(!feof(ek))
			{
				fwrite(&c,sizeof(c),1,ft);
				fread(&c,sizeof(c),1,ek);
			}
        } else if(a==2)
		{
			gotoxy(50,30);printf("Masukkan Harga Baru Sewa Mobil = Rp. "); getRp(&c.Harga,1,20,87,30);
			fwrite(&c,sizeof(c),1,ft);
			fread(&c,sizeof(c),1,ek);

			while(!feof(ek))
			{
				fwrite(&c,sizeof(c),1,ft);
				fread(&c,sizeof(c),1,ek);
			}
		}
		else if(a==3)
		{
		    masukkanKapasitasMobil:
            gotoxy(50,31); printf("[1] Tiga Orang");
            gotoxy(50,32); printf("[2] Empat Orang");
            gotoxy(50,33); printf("[3] Lima Orang");
            gotoxy(50,34); printf("[4] Enam Orang");
            gotoxy(50,35); printf("Kapasitas: ");
            getnum(&optTambahMobil,1);

            if (optTambahMobil == 1)
            {
                strcpy(c.Kapasitas, "Tiga Orang");
            } else if (optTambahMobil == 2)
            {
                strcpy(c.Kapasitas, "Empat Orang");
            } else if (optTambahMobil == 3)
            {
                strcpy(c.Kapasitas, "Lima Orang");
            } else if (optTambahMobil == 4)
            {
                strcpy(c.Kapasitas, "Enam Orang");
            } else
            {
                MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan..."," ATTENTION ",MB_OK);
                goto masukkanKapasitasMobil;
            }

			fwrite(&c,sizeof(c),1,ft);
			fread(&c,sizeof(c),1,ek);

			while(!feof(ek))
			{
				fwrite(&c,sizeof(c),1,ft);
				fread(&c,sizeof(c),1,ek);
			}
		}
		else
		if(a==4)
		{
			masukkanStatusMobil:
            gotoxy(50,31); printf("[1] Tersedia");
            gotoxy(50,32); printf("[2] Tidak Tersedia");
            gotoxy(50,33); printf("Status: ");
            getnum(&optStatus,1);

            if (optStatus == 1)
            {
                strcpy(c.Status, "Tersedia");
            } else if (optStatus == 2)
            {
                strcpy(c.Status, "Tidak Tersedia");
            } else
            {
                MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan..."," ATTENTION ",MB_OK);
                goto masukkanStatusMobil;
            }

			fwrite(&c,sizeof(c),1,ft);
			fread(&c,sizeof(c),1,ek);

			while(!feof(ek))
			{
				fwrite(&c,sizeof(c),1,ft);
				fread(&c,sizeof(c),1,ek);
			}
		}
		else
		if(a==5)
		{
			system("cls");
			MasterMobilMenu();
		}
		else
		{
		    MessageBox(NULL, "Pilihan tidak tersedia"," ATTENTION ",MB_OK);
			EditMobil();
		}
		fclose(ek);
		fclose(ft);

		ft = fopen("database/admin/mobilRecordTemp.dat", "rb");
		ek = fopen("database/admin/mobilRecord.dat", "wb");

		fread (&c, sizeof(c),1,ft);
		while(!feof(ft))
		{
			fwrite (&c, sizeof (c),1,ek);
			fread (&c, sizeof (c),1,ft);
		}
		fclose(ek);
		fclose(ft);

        MessageBox(NULL, "Mobil berhasil di update"," ATTENTION ",MB_OK);

        sd:
		gotoxy(50,38); printf("Do you want to edit more[Y/N]??");
        scanf(" %c", &ans);
        if (toupper(ans) == 'Y')
        {
            EditMobil();
        } else if (toupper(ans) == 'N')
        {
            MessageBox(NULL, "Thank you :) :)"," ATTENTION ",MB_OK);
            MasterMobilMenu();
        } else
        {
            MessageBox(NULL, "Invalid Input"," ATTENTION ",MB_OK);
            goto sd;
        }
	}

    MessageBox(NULL, "Mobil tidak tersedia"," ATTENTION ",MB_OK);
	system("cls");

	remove("database/admin/mobilRecord.dat");
    rename("database/admin/mobilRecordTemp.dat", "database/admin/mobilRecord.dat");

	MasterMobilMenu();
}

void HapusMobil()
{
    int found = 0;
    int IDCar;
    system("cls");

    OutterBorder();
	BersihKanan();
	BersihKiri();

    FILE *ek, *ft;

    ft = fopen("database/admin/mobilRecordTemp2.dat", "wb");
    ek = fopen("database/admin/mobilRecord.dat", "rb");

    gotoxy(50,40); printf("Tekan 0 untuk membatalkan");

    gotoxy(50,14); printf("Hapus Mobil");

    gotoxy(50,16);
    printf("Masukkan ID Car yang ingin dihapus: CAR");
    getnum(&IDCar,4);

    if (IDCar == 0)
    {
        MasterMobilMenu();
    }

    fread (&c, sizeof(c),1,ek);
	while (found != 1 && !feof(ek))
	{
		if (c.No == IDCar)
		{
			found = 1;
			break;
		}else
		{
			fwrite (&c, sizeof (c),1,ft);
			fread (&c, sizeof(c),1,ek);
		}
	}

	if (found == 1)
	{
		fread (&c, sizeof(c),1,ek);
		while (!feof(ek))
		{
			fwrite (&c, sizeof (c),1,ft);
			fread (&c, sizeof(c),1,ek);
		}
	}
	else
	{
	    MessageBox(NULL, "Mobil Belum Tersedia"," ATTENTION ",MB_OK);
		system("cls");
		MasterMobilMenu();
	}
	fclose(ft);
	fclose(ek);

	ek = fopen("database/admin/mobilRecord.dat", "wb");
	ft = fopen("database/admin/mobilRecordTemp2.dat", "rb");

	fread (&c, sizeof(c),1,ft);
	while(!feof(ft))
	{
		fwrite (&c, sizeof (c),1,ek);
		fread (&c, sizeof(c),1,ft);
	}
	fclose(ek);
	fclose(ft);

    MessageBox(NULL, "Mobil Berhasil Dihapus"," ATTENTION ",MB_OK);
	system("cls");

	remove("database/admin/mobilRecord.dat");
    rename("database/admin/mobilRecordTemp2.dat", "database/admin/mobilRecord.dat");

	MasterMobilMenu();
}

#define masterMobil
#endif // masterMobil
