#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// ===================================================
//                  STRUCT DATA
// ===================================================

struct Petugas {
    string id_petugas;
    string username;
    string password;
    string nama;
};

struct Anggota {
    string id_anggota;
    string kode_anggota;
    string nama;
    string alamat;
    string email;
    int status; // 0 = aktif, 1 = diblokir
};

struct Buku {
    string id_buku;
    string judul;
    string penulis;
    string penerbit;
    int tahun;
    int stok;
};

struct Peminjaman {
    string id_pinjam;
    string id_anggota;
    string id_buku;
    string tanggal_pinjam;
    string tanggal_kembali;
    int status; // 0 = belum kembali, 1 = sudah
};

// ===================================================
//                  ARRAY PENYIMPANAN
// ===================================================

Petugas datapetugas[100];
Anggota dataanggota[100];
Buku databuku[200];
Peminjaman datapinjam[300];

int jumlahpetugas = 0;
int jumlahanggota = 0;
int jumlahbuku = 0;
int jumlahpinjam = 0;

// ===================================================
//              FILE HANDLING GENERIC
// ===================================================

void savePetugas() {
    ofstream f("petugas.txt");
    for (int i = 0; i < jumlahpetugas; i++) {
        f << datapetugas[i].id_petugas << "|"
          << datapetugas[i].username << "|"
          << datapetugas[i].password << "|"
          << datapetugas[i].nama << "\n";
    }
}

void loadPetugas() {
    ifstream f("petugas.txt");
    jumlahpetugas = 0;

    string line;
    while (getline(f, line)) {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        datapetugas[jumlahpetugas].id_petugas = line.substr(0, p1);
        datapetugas[jumlahpetugas].username   = line.substr(p1 + 1, p2 - p1 - 1);
        datapetugas[jumlahpetugas].password   = line.substr(p2 + 1, p3 - p2 - 1);
        datapetugas[jumlahpetugas].nama       = line.substr(p3 + 1);

        jumlahpetugas++;
    }
}

void saveAnggota() {
    ofstream f("anggota.txt");
    for (int i = 0; i < jumlahanggota; i++) {
        f << dataanggota[i].id_anggota << "|"
          << dataanggota[i].kode_anggota << "|"
          << dataanggota[i].nama << "|"
          << dataanggota[i].alamat << "|"
          << dataanggota[i].email << "|"
          << dataanggota[i].status << "\n";
    }
}

void loadAnggota() {
    ifstream f("anggota.txt");
    jumlahanggota = 0;

    string line;
    while (getline(f, line)) {
        size_t a = line.find('|');
        size_t b = line.find('|', a + 1);
        size_t c = line.find('|', b + 1);
        size_t d = line.find('|', c + 1);
        size_t e = line.find('|', d + 1);

        dataanggota[jumlahanggota].id_anggota   = line.substr(0, a);
        dataanggota[jumlahanggota].kode_anggota = line.substr(a + 1, b - a - 1);
        dataanggota[jumlahanggota].nama         = line.substr(b + 1, c - b - 1);
        dataanggota[jumlahanggota].alamat       = line.substr(c + 1, d - c - 1);
        dataanggota[jumlahanggota].email        = line.substr(d + 1, e - d - 1);
        dataanggota[jumlahanggota].status       = stoi(line.substr(e + 1));

        jumlahanggota++;
    }
}

void saveBuku() {
    ofstream f("buku.txt");
    for (int i = 0; i < jumlahbuku; i++) {
        f << databuku[i].id_buku << "|"
          << databuku[i].judul << "|"
          << databuku[i].penulis << "|"
          << databuku[i].penerbit << "|"
          << databuku[i].tahun << "|"
          << databuku[i].stok << "\n";
    }
}

void loadBuku() {
    ifstream f("buku.txt");
    jumlahbuku = 0;

    string line;
    while (getline(f, line)) {
        size_t a = line.find('|');
        size_t b = line.find('|', a + 1);
        size_t c = line.find('|', b + 1);
        size_t d = line.find('|', c + 1);
        size_t e = line.find('|', d + 1);

        databuku[jumlahbuku].id_buku  = line.substr(0, a);
        databuku[jumlahbuku].judul    = line.substr(a + 1, b - a - 1);
        databuku[jumlahbuku].penulis  = line.substr(b + 1, c - b - 1);
        databuku[jumlahbuku].penerbit = line.substr(c + 1, d - c - 1);
        databuku[jumlahbuku].tahun    = stoi(line.substr(d + 1, e - d - 1));
        databuku[jumlahbuku].stok     = stoi(line.substr(e + 1));

        jumlahbuku++;
    }
}

void savePinjam() {
    ofstream f("pinjam.txt");
    for (int i = 0; i < jumlahpinjam; i++) {
        f << datapinjam[i].id_pinjam << "|"
          << datapinjam[i].id_anggota << "|"
          << datapinjam[i].id_buku << "|"
          << datapinjam[i].tanggal_pinjam << "|"
          << datapinjam[i].tanggal_kembali << "|"
          << datapinjam[i].status << "\n";
    }
}

void loadPinjam() {
    ifstream f("pinjam.txt");
    jumlahpinjam = 0;

    string line;
    while (getline(f, line)) {
        size_t a = line.find('|');
        size_t b = line.find('|', a + 1);
        size_t c = line.find('|', b + 1);
        size_t d = line.find('|', c + 1);
        size_t e = line.find('|', d + 1);

        datapinjam[jumlahpinjam].id_pinjam       = line.substr(0, a);
        datapinjam[jumlahpinjam].id_anggota      = line.substr(a + 1, b - a - 1);
        datapinjam[jumlahpinjam].id_buku         = line.substr(b + 1, c - b - 1);
        datapinjam[jumlahpinjam].tanggal_pinjam  = line.substr(c + 1, d - c - 1);
        datapinjam[jumlahpinjam].tanggal_kembali = line.substr(d + 1, e - d - 1);
        datapinjam[jumlahpinjam].status          = stoi(line.substr(e + 1));

        jumlahpinjam++;
    }
}

// ===================================================
//                CRUD PETUGAS
// ===================================================

void tambahPetugas() {
    Petugas p;

    cout << "\nID Petugas   : ";
    cin >> p.id_petugas;
    cout << "Username     : ";
    cin >> p.username;
    cout << "Password     : ";
    cin >> p.password;
    cout << "Nama Petugas : ";
    cin.ignore();
    getline(cin, p.nama);

    datapetugas[jumlahpetugas++] = p;
    savePetugas();
}

void lihatPetugas() {
    cout << "\n=== DATA PETUGAS ===\n";
    for (int i = 0; i < jumlahpetugas; i++) {
        cout << i+1 << ". " << datapetugas[i].id_petugas
             << " - " << datapetugas[i].nama << "\n";
    }
}

// ===================================================
//                CRUD ANGGOTA
// ===================================================

void tambahAnggota() {
    Anggota a;

    cout << "\nID Anggota   : ";
    cin >> a.id_anggota;
    cout << "Kode Anggota : ";
    cin >> a.kode_anggota;
    cout << "Nama         : ";
    cin.ignore();
    getline(cin, a.nama);
    cout << "Alamat       : ";
    getline(cin, a.alamat);
    cout << "Email        : ";
    getline(cin, a.email);

    a.status = 0;

    dataanggota[jumlahanggota++] = a;
    saveAnggota();
}

void lihatAnggota() {
    cout << "\n=== DATA ANGGOTA ===\n";
    for (int i = 0; i < jumlahanggota; i++) {
        cout << i+1 << ". " << dataanggota[i].id_anggota
             << " - " << dataanggota[i].nama << "\n";
    }
}

// ===================================================
//               CRUD BUKU
// ===================================================

void tambahBuku() {
    Buku b;

    cout << "\nID Buku   : ";
    cin >> b.id_buku;
    cout << "Judul     : ";
    cin.ignore();
    getline(cin, b.judul);
    cout << "Penulis   : ";
    getline(cin, b.penulis);
    cout << "Penerbit  : ";
    getline(cin, b.penerbit);
    cout << "Tahun     : ";
    cin >> b.tahun;
    cout << "Stok      : ";
    cin >> b.stok;

    databuku[jumlahbuku++] = b;
    saveBuku();
}

void lihatBuku() {
    cout << "\n=== DATA BUKU ===\n";
    for (int i = 0; i < jumlahbuku; i++) {
        cout << i+1 << ". " << databuku[i].id_buku
             << " - " << databuku[i].judul
             << " (" << databuku[i].stok << " tersedia)\n";
    }
}

// ===================================================
//              PEMINJAMAN - PENGEMBALIAN
// ===================================================

void pinjamBuku() {
    Peminjaman p;

    cout << "\nID Pinjam        : ";
    cin >> p.id_pinjam;
    cout << "ID Anggota       : ";
    cin >> p.id_anggota;
    cout << "ID Buku          : ";
    cin >> p.id_buku;
    cout << "Tanggal Pinjam   : ";
    cin >> p.tanggal_pinjam;

    p.tanggal_kembali = "-";
    p.status = 0;

    datapinjam[jumlahpinjam++] = p;
    savePinjam();

    // kurangi stok buku
    for (int i = 0; i < jumlahbuku; i++) {
        if (databuku[i].id_buku == p.id_buku) {
            databuku[i].stok--;
            break;
        }
    }
    saveBuku();
}

void kembalikanBuku() {
    string id;
    cout << "\nMasukkan ID Peminjaman : ";
    cin >> id;

    for (int i = 0; i < jumlahpinjam; i++) {
        if (datapinjam[i].id_pinjam == id) {
            cout << "Tanggal Kembali : ";
            cin >> datapinjam[i].tanggal_kembali;
            datapinjam[i].status = 1;
            savePinjam();

            // tambah stok kembali
            for (int j = 0; j < jumlahbuku; j++) {
                if (databuku[j].id_buku == datapinjam[i].id_buku) {
                    databuku[j].stok++;
                    break;
                }
            }
            saveBuku();

            return;
        }
    }
    cout << "ID peminjaman tidak ditemukan.\n";
}

// ===================================================
//                    MENU
// ===================================================

void menuPetugas() {
    int pilih;
    do {
        cout << "\n=== MENU PETUGAS ===\n";
        cout << "1. Tambah Petugas\n";
        cout << "2. Lihat Petugas\n";
        cout << "3. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) tambahPetugas();
        else if (pilih == 2) lihatPetugas();

    } while (pilih != 3);
}

void menuAnggota() {
    int pilih;
    do {
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

void menuPinjam() {
    int pilih;
    do {
        cout << "\n=== MENU PEMINJAMAN ===\n";
        cout << "1. Pinjam Buku\n";
        cout << "2. Kembalikan Buku\n";
        cout << "3. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) pinjamBuku();
        else if (pilih == 2) kembalikanBuku();

    } while (pilih != 3);
}

// ===================================================
//                   MAIN MENU
// ===================================================

int main() {
    loadPetugas();
    loadAnggota();
    loadBuku();
    loadPinjam();

    int pilih;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Petugas\n";
        cout << "2. Anggota\n";
        cout << "3. Buku\n";
        cout << "4. Peminjaman\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) menuPetugas();
        else if (pilih == 2) menuAnggota();
        else if (pilih == 3) menuBuku();
        else if (pilih == 4) menuPinjam();

    } while (pilih != 5);

    return 0;
}
