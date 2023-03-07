#ifndef adminMainMenu

/* ********* ADMIN ********* */
/* ********* MAIN MENU ********* */

bool found, founds;

struct adminPenyewaan
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

struct adminPenyewaan admPnyw;

struct adminMobil
{
    int No;
	char Tipe[25];
	int Harga;
	char Kapasitas[50];
	char Status[25];
};

struct adminMobil ubahStatusMbl;

struct adminSupir
{
    int No;
    char namaLengkap[50];
    int harga;
    char phone[50];
    char status[50];
};

struct adminSupir ubahStatusSpr;


void AdminMainMenu()
{
    system("cls");
    int choose;

    OutterBorder();
	BersihKanan();
	BersihKiri();

    gotoxy(4,14); printf("Menu Admin");
    gotoxy(4,15); printf("Pilih Opsi: ");

    gotoxy(4,16);printf("1. Master Mobil");
    gotoxy(4,17);printf("2. Master Supir");
    gotoxy(4,18);printf("3. Master User");
    gotoxy(4,19);printf("4. Daftar Pemesanan Aktif");
    gotoxy(4,20);printf("99. Logout");

    gotoxy(4,21);printf("Pilihan Opsi: ");
    scanf("%i", &choose);

    switch(choose)
    {
        case 1:
            MasterMobilMenu();
            break;

        case 2:
            MasterSupirMenu();
            break;

        case 3:
            MasterUserMenu();
            break;

        case 4:
            PenyelesaianSewa();
            break;

        case 99:
            adminLogout();
            break;

        default:
            gotoxy(60,33);printf("Angka tidak sesuai, tekan untuk melanjutkan....\n");
            getch();

            AdminMainMenu();
    }
}

void PenyelesaianSewa()
{
    gotoxy(43,13); printf("Riwayat Penyewaan");

    int y, kodeSelesai, row;
	char hargarp[20], hargarpBayar[20], hargarpKembali[20], keterangan[30], ans;

	FILE *transaksi, *baruTransaksi;
	transaksi = fopen("database/customer/transaksi.dat", "rb");
    baruTransaksi = fopen("database/customer/trsTransaksi.dat", "wb");

    gotoxy(43,40); printf("Tekan 0 untuk membatalkan");

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

    found = false;
	fread(&admPnyw,sizeof(admPnyw),1,transaksi);
	while(!feof(transaksi))
	{
        if (!strcmp(admPnyw.status, "Penyewaan"))
        {
            gotoxy(43,row);
            printf("PNYW%d",admPnyw.kodePenyewaan); fflush(stdin);

            gotoxy(53,row);
            printf("%s", admPnyw.namaMobil); fflush(stdin);

            gotoxy(73,row);
            printf("%s", admPnyw.namaSupir); fflush(stdin);

            gotoxy(93,row);
            printf("%s", admPnyw.namaUser); fflush(stdin);

            rupiah(admPnyw.harga, hargarp);
            gotoxy(113,row);
            printf("%s", hargarp); fflush(stdin);
            row++;

            fread(&admPnyw,sizeof(admPnyw),1,transaksi);
        }
        else
        {
            fwrite(&admPnyw,sizeof(admPnyw),1,baruTransaksi);
            fread(&admPnyw,sizeof(admPnyw),1,transaksi);
        }

	}

	gotoxy(43,row + 3); printf("Masukkan penyewaan yang ingin diselesaikan: PNYW");
	fflush(stdin); getnum(&kodeSelesai,6);

    if (kodeSelesai == 0)
    {
        AdminMainMenu();
    }

	FILE *transaksiSelesai, *baruTransaksiSelesai;
	transaksiSelesai = fopen("database/customer/transaksi.dat", "rb");
    baruTransaksiSelesai = fopen("database/customer/trs2Transaksi.dat", "wb");

    strcpy(keterangan, "Penyewaan");

    founds = false;
	fread(&admPnyw,sizeof(admPnyw),1,transaksiSelesai);
	while((!founds)&&(!feof(transaksiSelesai)))
	{
        if (admPnyw.kodePenyewaan == kodeSelesai && (!strcmp(admPnyw.status, keterangan)))
        {
            founds = true;
        }
        else
        {
            fwrite(&admPnyw,sizeof(admPnyw),1,baruTransaksiSelesai);
            fread(&admPnyw,sizeof(admPnyw),1,transaksiSelesai);
        }
	}

	if (founds == true)
    {
        OutterBorder();
        BersihKanan();
        BersihKiri();

        gotoxy(43,13); printf("Konfirmasi Penyelesaian Sewa");

        gotoxy(43,15); printf("Kode Penyewaan: PNYW%d", admPnyw.kodePenyewaan); fflush(stdin);
        gotoxy(43,16); printf("Tanggal Transaksi: %d-%d-%d", admPnyw.tgl, admPnyw.bulan, admPnyw.tahun); fflush(stdin);
        gotoxy(43,17); printf("Nama Mobil: %s", admPnyw.namaMobil); fflush(stdin);
        gotoxy(43,18); printf("Nama Supir: %s", admPnyw.namaSupir); fflush(stdin);
        gotoxy(43,19); printf("Nama User: %s", admPnyw.namaUser); fflush(stdin);
        gotoxy(43,20); printf("SIM: %s", admPnyw.sim); fflush(stdin);
        gotoxy(43,21); printf("NIK: %s", admPnyw.nik); fflush(stdin);
        gotoxy(43,22); printf("Alamat Tempat Tinggal: %s", admPnyw.alamatTempatTinggal); fflush(stdin);
        gotoxy(43,23); printf("Umur: %d", admPnyw.umur); fflush(stdin);
        gotoxy(43,24); printf("Jumlah Hari: %d", admPnyw.jumlahHari); fflush(stdin);
        gotoxy(43,25); printf("Harga: %d", admPnyw.harga); fflush(stdin);
        gotoxy(43,26); printf("Status: %s", admPnyw.status); fflush(stdin);
        getch();

        sd:
		gotoxy(43,29); printf("Yakin untuk mengubah status menjadi pengembalian[Y/N]??");
        scanf(" %c", &ans);
        if (toupper(ans) == 'Y')
        {
            strcpy(admPnyw.status, "Pengembalian");


            /* ================== MENGUBAH STATUS MOBIL ================== */

            FILE *bacaDataMobil, *tulisDataMobil;
            char tersedia[50];

            found = false;

            strcpy(tersedia, "Tersedia");

            bacaDataMobil = fopen("database/admin/mobilRecord.dat", "rb");
            tulisDataMobil = fopen("database/admin/mobilRecordTemp.dat", "wb");

            fread (&ubahStatusMbl, sizeof(ubahStatusMbl), 1, bacaDataMobil);
            while(!feof(bacaDataMobil))
            {
                if (ubahStatusMbl.No == admPnyw.idMobil)
                {
                    strcpy(ubahStatusMbl.Status, tersedia);
                    fwrite(&ubahStatusMbl, sizeof(ubahStatusMbl), 1, tulisDataMobil);
                } else
                {
                    fwrite(&ubahStatusMbl, sizeof(ubahStatusMbl), 1, tulisDataMobil);
                }
                fread (&ubahStatusMbl, sizeof(ubahStatusMbl), 1, bacaDataMobil);
            }
            fclose(bacaDataMobil);
            fclose(tulisDataMobil);

            bacaDataMobil = fopen("database/admin/mobilRecord.dat", "wb");
            tulisDataMobil = fopen("database/admin/mobilRecordTemp.dat", "rb");

            fread(&ubahStatusMbl, sizeof(ubahStatusMbl), 1, tulisDataMobil);
            while(!feof(tulisDataMobil))
            {
                fwrite(&ubahStatusMbl, sizeof(ubahStatusMbl), 1, bacaDataMobil);
                fread(&ubahStatusMbl, sizeof(ubahStatusMbl), 1, tulisDataMobil);
            }

            fclose(bacaDataMobil);
            fclose(tulisDataMobil);


            /* ================== MENGUBAH STATUS SUPIR ================== */

            FILE *bacaDataSupir, *tulisDataSupir;
            char tersediaSupir[50];

            found = false;

            strcpy(tersediaSupir, "Tersedia");

            bacaDataSupir = fopen("database/supir.dat", "rb");
            tulisDataSupir = fopen("database/supirTemp.dat", "wb");

            fread (&ubahStatusSpr, sizeof(ubahStatusSpr), 1, bacaDataSupir);
            while(!feof(bacaDataSupir))
            {
                if (ubahStatusSpr.No == admPnyw.idSupir)
                {
                    strcpy(ubahStatusSpr.status, tersediaSupir);
                    fwrite(&ubahStatusSpr, sizeof(ubahStatusSpr), 1, tulisDataSupir);
                } else
                {
                    fwrite(&ubahStatusSpr, sizeof(ubahStatusSpr), 1, tulisDataSupir);
                }
                fread (&ubahStatusSpr, sizeof(ubahStatusSpr), 1, bacaDataSupir);
            }
            fclose(bacaDataSupir);
            fclose(tulisDataSupir);

            bacaDataSupir = fopen("database/supir.dat", "wb");
            tulisDataSupir = fopen("database/supirTemp.dat", "rb");

            fread(&ubahStatusSpr, sizeof(ubahStatusSpr), 1, tulisDataSupir);
            while(!feof(tulisDataSupir))
            {
                fwrite(&ubahStatusSpr, sizeof(ubahStatusSpr), 1, bacaDataSupir);
                fread(&ubahStatusSpr, sizeof(ubahStatusSpr), 1, tulisDataSupir);
            }

            fclose(bacaDataSupir);
            fclose(tulisDataSupir);


            /* ================== MENGISI DATA DARI TEMP ================== */

            fwrite(&admPnyw,sizeof(admPnyw),1,baruTransaksiSelesai);
            fread(&admPnyw,sizeof(admPnyw),1,transaksiSelesai);

            while(!feof(transaksiSelesai))
            {
                fwrite(&admPnyw,sizeof(admPnyw),1,baruTransaksiSelesai);
                fread(&admPnyw,sizeof(admPnyw),1,transaksiSelesai);
            }

            fclose(transaksiSelesai);
            fclose(baruTransaksiSelesai);

            MessageBox(NULL, "Status sudah berubah menjadi pengembalian"," ATTENTION ",MB_OK);

            transaksiSelesai = fopen("database/customer/transaksi.dat", "wb");
            baruTransaksiSelesai = fopen("database/customer/trs2Transaksi.dat", "rb");

            fread (&admPnyw, sizeof(admPnyw),1,baruTransaksiSelesai);
            while(!feof(baruTransaksiSelesai))
            {
                fwrite (&admPnyw, sizeof (admPnyw),1,transaksiSelesai);
                fread (&admPnyw, sizeof (admPnyw),1,baruTransaksiSelesai);
            }
            fclose(transaksiSelesai);
            fclose(baruTransaksiSelesai);

            AdminMainMenu();
        } else if (toupper(ans) == 'N')
        {
            MessageBox(NULL, "Status tidak berubah"," ATTENTION ",MB_OK);
            AdminMainMenu();
        } else
        {
            MessageBox(NULL, "Invalid Input"," ATTENTION ",MB_OK);
            goto sd;
        }
    } else
    {
        MessageBox(NULL, "Kode Penyewaan Sudah Tidak Berlaku"," ATTENTION ",MB_OK);
        BersihKanan();
        AdminMainMenu();

        fclose(transaksiSelesai);
        fclose(baruTransaksiSelesai);
    }
}

/* ********* EXIT SCREEN ********* */

void adminLogout() // function to exit
{
    MessageBox(NULL, "Berhasil Logout, tekan untuk melanjutkan..."," ATTENTION ",MB_OK);

    system("cls");
    LoginForm();
}

#define adminMainMenu
#endif // adminMainMenu
