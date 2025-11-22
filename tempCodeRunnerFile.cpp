#include <iostream>
#include <string>
using namespace std;

struct Anggota {
    string id_anggota; 
    string kode_anggota;
    string nama;
    string alamat;
    string email;
    int status;
};

struct Buku {
    string id_buku;
    string isbn;
    string judul;
    string pengarang;
    string penerbit;
    int tahun_terbit;
    int stok;
};

struct Peminjaman {
    string id_peminjaman;
    string id_anggota;
    string id_buku;
    string tanggal_pinjam;
    string tanggal_kembali;
    int status;
    int denda;
};

struct Petugas {
    string id_petugas;
    string username;
    string password;
    string nama;
};

Anggota dataanggota[50];
Buku databuku[100];
Petugas datapetugas[5];

int jumlahanggota = 0;
int jumlahbuku = 0;
int jumlahpetugas = 0;
int jumlahpeminjaman = 0;

void menuUtama();
void menuAnggota();
void menuBuku();


// ============ PETUGAS ============

void tambahPetugas() {
    datapetugas[0].id_petugas = "000001";
    datapetugas[0].username = "admin";
    datapetugas[0].password = "admin123";
    datapetugas[0].nama = "Petugas Utama";
    jumlahpetugas = 1;
}

void loginPetugas() {
    string u, p;

    while (true) {
        system("cls");
        cout << "\n--- LOGIN PETUGAS ---\n";
        cout << "Username : ";
        cin >> u;
        cout << "Password : ";
        cin >> p;

        for (int i = 0; i < jumlahpetugas; i++) {
            if (u == datapetugas[i].username && p == datapetugas[i].password) {
                cout << "\nLogin berhasil. Selamat datang. " 
                     << datapetugas[i].nama << "!\n";
                return; 
            }
        }

        cout << "\nLogin gagal! Username atau password salah.\n";
        cout << "Coba lagi ya.\n\n";
    }
}

// ============ ANGGOTA ============

string generateKodeAnggota(string tahun, string bulan, string tanggal) {
    string dasar = tahun + bulan + tanggal;

    int hitung = 0;

    for (int i = 0; i < jumlahanggota; i++) {
        if (dataanggota[i].id_anggota.substr(0, 8) == dasar) {
            hitung++;
        }
    }

    hitung++;

    string urut = "";
    if (hitung < 10) urut = "00" + to_string(hitung);
    else if (hitung < 100) urut = "0" + to_string(hitung);
    else urut = to_string(hitung);

    return dasar + urut;
}


void tambahAnggota() {
    cout << "\n--- TAMBAH ANGGOTA ---\n";

    Anggota a;
    cin.ignore();

    cout << "Nama   : ";
    getline(cin, a.nama);

    cout << "Alamat : ";
    getline(cin, a.alamat);

    cout << "Email  : ";
    getline(cin, a.email);

    string tahun, bulan, tanggal;
    cout << "Tahun Lahir (YYYY): ";
    cin >> tahun;
    cout << "Bulan Lahir (MM): ";
    cin >> bulan;
    cout << "Tanggal Lahir (DD): ";
    cin >> tanggal;

    a.id_anggota = generateKodeAnggota(tahun, bulan, tanggal);
    a.kode_anggota = a.id_anggota;
    a.status = 1;

    dataanggota[jumlahanggota] = a;
    jumlahanggota++;

    cout << "\nAnggota berhasil ditambahkan!\n";
    cout << "Kode Anggota: " << a.kode_anggota << endl;
}


void lihatAnggota() {
    cout << "\n=== DATA ANGGOTA ===\n";

    if (jumlahanggota == 0) {
        cout << "Belum ada data anggota.\n";
        return;
    }

    for (int i = 0; i < jumlahanggota; i++) {
        cout << i + 1 << ". " << dataanggota[i].nama << endl;
        cout << "   ID     : " << dataanggota[i].id_anggota << endl;
        cout << "   Alamat : " << dataanggota[i].alamat << endl;
        cout << "   Email  : " << dataanggota[i].email << endl;
        cout << "   Status : " << (dataanggota[i].status == 1 ? "Aktif" : "Nonaktif") << endl;
        cout << "-----------------------------------\n";
    }
}

void tampilAnggotaAscending() {
    for (int i = 0; i < jumlahanggota - 1; i++) {
        for (int j = i + 1; j < jumlahanggota; j++) {
            if (dataanggota[i].nama > dataanggota[j].nama) {
                Anggota temp = dataanggota[i];
                dataanggota[i] = dataanggota[j];
                dataanggota[j] = temp;
            }
        }
    }

    for (int i = 0; i < jumlahanggota; i++) {
        cout << dataanggota[i].kode_anggota << " - " << dataanggota[i].nama << endl;
    }
}


void menuAnggota() {
    int pilih;
    do {
        system("cls");
        cout << "\n=== MENU ANGGOTA ===\n";
        cout << "1. Tambah Anggota\n";
        cout << "2. Lihat Anggota\n";
        cout << "3. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) tambahAnggota();
        else if (pilih == 2) lihatAnggota();

    } while (pilih != 3);
}


// ============ BUKU ============

string generateIdBuku() {
    int urut = jumlahbuku + 1;
    string id = "BK";
    if (urut < 10) id += "00" + to_string(urut);
    else if (urut < 100) id += "0" + to_string(urut);
    else id += to_string(urut);
    return id;
}

void tampilBukuAscending() {
    for (int i = 0; i < jumlahbuku - 1; i++) {
        for (int j = i + 1; j < jumlahbuku; j++) {
            if (databuku[i].judul > databuku[j].judul) {
                Buku temp = databuku[i];
                databuku[i] = databuku[j];
                databuku[j] = temp;
            }
        }
    }

    for (int i = 0; i < jumlahbuku; i++) {
        cout << databuku[i].id_buku << " - " << databuku[i].judul << " - " 
             << databuku[i].pengarang << " - " << databuku[i].stok << endl;
    }
}

void tambahBuku() {
    cout << "\nTambah Buku\n";

    cin.ignore();
    databuku[jumlahbuku].id_buku = generateIdBuku();

    cout << "ISBN: ";
    getline(cin, databuku[jumlahbuku].isbn);

    cout << "Judul: ";
    getline(cin, databuku[jumlahbuku].judul);

    cout << "Pengarang: ";
    getline(cin, databuku[jumlahbuku].pengarang);

    cout << "Penerbit: ";
    getline(cin, databuku[jumlahbuku].penerbit);

    cout << "Tahun terbit: ";
    cin >> databuku[jumlahbuku].tahun_terbit;

    cout << "Stok: ";
    cin >> databuku[jumlahbuku].stok;

    jumlahbuku++;
    cout << "Buku berhasil ditambahkan.\n";
}

void lihatBuku() {
    cout << "\n=== DATA BUKU ===\n";

    if (jumlahbuku == 0) {
        cout << "Belum ada data buku.\n";
        return;
    }

    for (int i = 0; i < jumlahbuku; i++) {
        cout << databuku[i].id_buku << " - " << databuku[i].judul << endl;
    }
}



void menuBuku() {
    int pilih;
    do {
        cout << "\n=== MENU BUKU ===\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Lihat Buku\n";
        cout << "3. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) tambahBuku();
        else if (pilih == 2) lihatBuku();

    } while (pilih != 3);
}

// ============ MENU UTAMA ============

void menuUtama() {
    int pilih;
    do {
        system("cls");
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Menu Anggota\n";
        cout << "2. Menu Buku\n";
        cout << "3. Menu Peminjaman\n";
        cout << "4. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) menuAnggota();
        else if (pilih == 2) menuBuku();
        else if (pilih == 4) break;

    } while (true);
}

// ============ MAIN ============

int main() {
    tambahPetugas();
    loginPetugas();
    menuUtama();
    return 0;
}
