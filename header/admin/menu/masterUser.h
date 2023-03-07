#ifndef masterUser

struct mUser
{
    int No;
    char namaLengkap[50];
    char password[50];
    char phone[50];
    char role[50];
};

struct mUser mu;

struct mUserNew {
    int NoBaru;
    int PhoneBaru;
};

struct mUserNew mun;

int b;
char ans;

void MasterUserMenu()
{
    system("cls");
    int choose;

    OutterBorder();
	BersihKanan();
	BersihKiri();

    gotoxy(4,14);printf("Menu Admin - Master User");
    gotoxy(4,15);printf("Pilih Opsi: \n\n");

    gotoxy(4,16);printf("1. Tambah User \n");
    gotoxy(4,17);printf("2. Edit User \n");
    gotoxy(4,18);printf("3. Hapus User \n");
    gotoxy(4,19);printf("99. Kembali \n");

    LihatUser();

    gotoxy(4,20);printf("Pilihan Opsi: ");
    scanf("%i", &choose);

    switch(choose)
    {
        case 1:
            TambahUser();
            break;

        case 2:
            EditUser();
            break;

        case 3:
            HapusUser();
            break;

        case 99:
            AdminMainMenu();
            break;

        default:
            MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan..."," ATTENTION ",MB_OK);

            MasterUserMenu();
    }
}

void TambahUser()
{
    system("cls");

    OutterBorder();
	BersihKanan();
	BersihKiri();

    char ans;
    int id, optRole;
    FILE *ek, *fk;

    ek = fopen("database/users.dat", "ab");

    fk = fopen("database/users.dat", "rb");

    gotoxy(50,40); printf("Tekan 0 untuk membatalkan");

    fread(&mu, sizeof(mu), 1, fk);
    while(!feof(fk))
    {
        fread(&mu, sizeof(mu), 1, fk);
        id = mu.No;
    }

    fclose(fk);
    mu.No = id + 1;

    gotoxy(50,14); printf(" Tambah User");

    /* ********* No ********* */
    gotoxy(50,16); printf(" No: USR%d", mu.No);

    /* ********* Full Name ********* */
    gotoxy(50,17); printf(" Full Name: ");
    fflush(stdin);
    getteks(mu.namaLengkap, 50);

    if (!strcmp(mu.namaLengkap, "0"))
    {
        MasterUserMenu();
    }

    mu.namaLengkap[0] = toupper(mu.namaLengkap[0]);

    /* ********* Password ********* */
    gotoxy(50,18);printf(" Password: ");
    fflush(stdin);
    getteks(mu.password, 50);

    /* ********* Phone ********* */
    gotoxy(50,19);printf(" Phone: ");
    fflush(stdin);
    getteks(mu.phone, 50);

    /* ********* Role ********* */
    masukkanRoleUser:
    gotoxy(50,21); printf(" [1] Manager");
    gotoxy(50,22); printf(" [2] Admin");
    gotoxy(50,23); printf(" [3] Customer");
    gotoxy(50,24); printf(" Role: ");
    getnum(&optRole,1);

    if (optRole == 1)
    {
        strcpy(mu.role, "Manager");
    } else if (optRole == 2)
    {
        strcpy(mu.role, "Admin");
    } else if (optRole == 3)
    {
        strcpy(mu.role, "Customer");
    } else
    {
        MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan..."," ATTENTION ",MB_OK);
        goto masukkanRoleUser;
    }

    ek = fopen("database/users.dat", "ab");
    fwrite(&mu, sizeof(mu),1,ek);
	fclose(ek);

	MessageBox(NULL, "Information Record Successfull"," ATTENTION ",MB_OK);

    getch();
    sd:
    gotoxy(50,28);printf(" Do you want to add more[Y/N]??");
    scanf(" %c", &ans);
    if (toupper(ans) == 'Y')
    {
        TambahUser();
    } else if (toupper(ans) == 'N')
    {
        MessageBox(NULL, "Thank You"," ATTENTION ",MB_OK);
        MasterUserMenu();
    } else
    {
        MessageBox(NULL, "Invalid Input"," ATTENTION ",MB_OK);
        goto sd;
    }
}

void LihatUser()
{
    int row;

    FILE *ek;

    ek = fopen("database/users.dat", "rb");

    gotoxy(43,14); printf("Data User");

    gotoxy(43,16);
    printf("No");

    gotoxy(53,16);
    printf("Nama Lengkap");

    gotoxy(85,16);
    printf("Password");

    gotoxy(110,16);
    printf("Phone");

    gotoxy(130,16);
    printf("Role");

    gotoxy(41,17);
    printf("===================================================================================================================");

    row = 18;

    fread(&mu, sizeof(mu),1,ek);
	while (!feof(ek))
	{
	    gotoxy(43,row);
	    printf("USR%d",mu.No); fflush(stdin);

	    gotoxy(53,row);
	    printf("%s",mu.namaLengkap); fflush(stdin);

        gotoxy(85,row);
        printf("%s", mu.password); fflush(stdin);

        gotoxy(110,row);
        printf("%s", mu.phone); fflush(stdin);

        gotoxy(130,row);
        printf("%s", mu.role); fflush(stdin);
        row++;

		fread(&mu, sizeof(mu),1,ek);
	}
	fclose(ek);
}

void EditUser()
{
    FILE *ek, *ft;

    int found;
	int a, optRole;
	char harga[20], ans;

    system("cls");
    OutterBorder();
	BersihKanan();
	BersihKiri();

    ft = fopen("database/usersTemp.dat", "wb");
    ek = fopen("database/users.dat", "rb");

    gotoxy(50,40); printf("Tekan 0 untuk membatalkan");

	gotoxy(50,14); printf("Edit User");

    if (ek == NULL)
    {
        MessageBox(NULL, "Can not open file !!"," ATTENTION ",MB_OK);
        MasterUserMenu();
    }

    gotoxy(50,16);
    printf("Masukkan ID User yang ingin diupdate: USR");
    getnum(&mun.NoBaru,4);

    if (mun.NoBaru == 0)
    {
        MasterUserMenu();
    }

    found = 0;

    if (ft == NULL)
    {
        MessageBox(NULL, "Can not open file !!"," ATTENTION ",MB_OK);
        MasterUserMenu();
    }

    while (found != 1 && !feof(ek))
	{
		fread (&mu, sizeof(mu) , 1 , ek);
		if(mu.No == mun.NoBaru)
		{
			found = 1;
		}
		else
		{
			fwrite (&mu, sizeof (mu),1,ft);
		}
	}

	if(found == 1)
	{
	    gotoxy(50,18);	printf("ID User       = USR%d \n ", mu.No);
		gotoxy(50,19);	printf("Nama Lengkap     = %s \n ", mu.namaLengkap);
		gotoxy(50,20);	printf("Password = %s \n", mu.password);
		gotoxy(50,21);	printf("Phone = %s \n", mu.phone);
		gotoxy(50,22);	printf("Role  = %s \n", mu.role);

		gotoxy(50,24);	printf("Pilih data yang akan diupdate = \n");
		gotoxy(50,25);  printf("[1] Nama Lengkap \n");
		gotoxy(50,26);  printf("[2] Password \n");
		gotoxy(50,27);  printf("[3] Phone \n");
		gotoxy(50,28);	printf("[4] Role \n");
		gotoxy(50,29);	printf("[5] Batal \n");
		gotoxy(50,30);	printf("Pilih = ");
		getnum(&a,1);

		if (a==1)
        {
            gotoxy(50,31);printf("Masukkan Nama Lengkap= ");
            getteks(mu.namaLengkap, 50);
            mu.namaLengkap[0] = toupper(mu.namaLengkap[0]);

			fwrite(&mu,sizeof(mu),1,ft);
			fread(&mu,sizeof(mu),1,ek);

			while(!feof(ek))
			{
				fwrite(&mu,sizeof(mu),1,ft);
				fread(&mu,sizeof(mu),1,ek);
			}
        }else if(a==2)
		{
			gotoxy(50,31);	printf("Masukkan Password Baru = "); fflush(stdin);
            getteks(mu.password, 50);

			fwrite(&mu,sizeof(mu),1,ft);
			fread(&mu,sizeof(mu),1,ek);

			while(!feof(ek))
			{
				fwrite(&mu,sizeof(mu),1,ft);
				fread(&mu,sizeof(mu),1,ek);
			}
		}
		else if(a==3)
		{
			gotoxy(50,31);	printf("Masukkan Nomor Telepon Baru = "); fflush(stdin);
            getteks(mu.phone, 50);

			fwrite(&mu,sizeof(mu),1,ft);
			fread(&mu,sizeof(mu),1,ek);

			while(!feof(ek))
			{
				fwrite(&mu,sizeof(mu),1,ft);
				fread(&mu,sizeof(mu),1,ek);
			}
		}
		else
		if(a==4)
		{
		    masukkanRoleUser:
            gotoxy(50,31); printf("[1] Manager");
            gotoxy(50,32); printf("[2] Admin");
            gotoxy(50,33); printf("[3] Customer");
            gotoxy(50,34); printf("Masukkan Role Baru: ");
            getnum(&optRole,1);

            if (optRole == 1)
            {
                strcpy(mu.role, "Manager");
            } else if (optRole == 2)
            {
                strcpy(mu.role, "Admin");
            } else if (optRole == 3)
            {
                strcpy(mu.role, "Customer");
            } else
            {
                MessageBox(NULL, "Angka tidak sesuai, tekan untuk melanjutkan...\n"," ATTENTION ",MB_OK);
                goto masukkanRoleUser;
            }

			fwrite(&mu,sizeof(mu),1,ft);
			fread(&mu,sizeof(mu),1,ek);

			while(!feof(ek))
			{
				fwrite(&mu,sizeof(mu),1,ft);
				fread(&mu,sizeof(mu),1,ek);
			}
		}
		else
		if(a==5)
		{
			system("cls");
			MasterUserMenu();
		}
		else
		{
		    MessageBox(NULL, "Pilihan tidak tersedia"," ATTENTION ",MB_OK);
			EditUser();
		}
		fclose(ek);
		fclose(ft);

		ft = fopen("database/usersTemp.dat", "rb");
		ek = fopen("database/users.dat", "wb");

		fread (&mu, sizeof(mu),1,ft);
		while(!feof(ft))
		{
			fwrite (&mu, sizeof (mu),1,ek);
			fread (&mu, sizeof (mu),1,ft);
		}
		fclose(ek);
		fclose(ft);

        MessageBox(NULL, "User berhasil di update"," ATTENTION ",MB_OK);

		sd:
		gotoxy(50,38); printf("Do you want to edit more[Y/N]??");
        scanf(" %c", &ans);
        if (toupper(ans) == 'Y')
        {
            EditUser();
        } else if (toupper(ans) == 'N')
        {
            MessageBox(NULL, "Thank you"," ATTENTION ",MB_OK);
            MasterUserMenu();
        } else
        {
            MessageBox(NULL, "Invalid Input"," ATTENTION ",MB_OK);
            goto sd;
        }
	}

    MessageBox(NULL, "User tidak tersedia"," ATTENTION ",MB_OK);
	system("cls");

	remove("database/users.dat");
    rename("database/usersTemp.dat", "database/users.dat");

	MasterUserMenu();
}

void HapusUser()
{
    int found = 0;
    int IDBaru;
    system("cls");

    OutterBorder();
	BersihKanan();
	BersihKiri();

    FILE *ek, *ft;

    ft = fopen("database/usersTemp2.dat", "wb");
    ek = fopen("database/users.dat", "rb");

    gotoxy(50,40); printf("Tekan 0 untuk membatalkan");

    gotoxy(50,14); printf("Hapus User");

    gotoxy(50,16);
    printf("Masukkan ID User yang ingin dihapus: USR");
    getnum(&mun.NoBaru,20);

    if (mun.NoBaru == 0)
    {
        MasterUserMenu();
    }

    fread (&mu, sizeof(mu),1,ek);
	while (found != 1 && !feof(ek))
	{
		if (mu.No == mun.NoBaru)
		{
			found = 1;
			break;
		}else
		{
			fwrite (&mu, sizeof (mu),1,ft);
			fread (&mu, sizeof(mu),1,ek);
		}
	}

	if (found == 1)
	{
		fread (&mu, sizeof(mu),1,ek);
		while (!feof(ek))
		{
			fwrite (&mu, sizeof (mu),1,ft);
			fread (&mu, sizeof(mu),1,ek);
		}
	}
	else
	{
	    MessageBox(NULL, "User Belum Tersedia"," ATTENTION ",MB_OK);
		MasterUserMenu();
	}
	fclose(ft);
	fclose(ek);

	ek = fopen("database/users.dat", "wb");
	ft = fopen("database/usersTemp2.dat", "rb");
	fread (&mu, sizeof(mu),1,ft);
	while(!feof(ft))
	{
		fwrite (&mu, sizeof (mu),1,ek);
		fread (&mu, sizeof(mu),1,ft);
	}
	fclose(ek);
	fclose(ft);

    MessageBox(NULL, "User Berhasil Dihapus"," ATTENTION ",MB_OK);

	remove("database/users.dat");
    rename("database/usersTemp2.dat", "database/users.dat");

	MasterUserMenu();
}

#define masterUser
#endif // masterUser

