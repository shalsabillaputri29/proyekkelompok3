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
Petugas datapetugas[100];
Peminjaman datapeminjaman[100]; 
Petugas daftarPetugas[100];  

int jumlahanggota = 0;
int jumlahbuku = 0;
int jumlahpetugas = 0;
int jumlahpeminjaman = 0;

void menuUtama();
void menuAnggota();
void menuBuku();


// ============ PETUGAS ============

string generateIdPetugas() {
    int urut = jumlahpetugas + 1;
    string id = to_string(urut);

    // bikin jadi 6 digit (leading zero)
    while (id.length() < 6) {
        id = "0" + id;
    }
    return id;
}

void AkunDefault() {
    datapetugas[0].id_petugas = "000001";
    datapetugas[0].username = "admin";
    datapetugas[0].password = "admin123";
    datapetugas[0].nama = "Administrator";

    jumlahpetugas = 1;
}

void tambahPetugas() {
    system("cls");
    cout << "\n=== TAMBAH PETUGAS ===\n";

    string user, pass, nama;

    datapetugas[jumlahpetugas].id_petugas = generateIdPetugas();

    cout << "Username     : ";
    cin >> user;

    cout << "Password     : ";
    cin >> pass;

    cout << "Nama Petugas : ";
    cin.ignore();
    getline(cin, nama);

    datapetugas[jumlahpetugas].username = user;
    datapetugas[jumlahpetugas].password = pass;
    datapetugas[jumlahpetugas].nama = nama;

    jumlahpetugas++;

    cout << "\nPetugas berhasil ditambahkan!\n";
    cout << "ID Petugas: " << datapetugas[jumlahpetugas-1].id_petugas << endl;
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

void lihatPetugas() {
    system("cls");
    cout << "\n=== DATA PETUGAS ===\n";

    if (jumlahpetugas == 0) {
        cout << "Belum ada data petugas.\n";
        return;
    }

    for (int i = 0; i < jumlahpetugas; i++) {
        cout << "\nPetugas ke-" << i + 1 << endl;
        cout << "ID Petugas : " << datapetugas[i].id_petugas << endl;
        cout << "Username   : " << datapetugas[i].username << endl;
        cout << "Nama       : " << datapetugas[i].nama << endl;
    }
}


void menuPetugas() {
    int pilih;

    do {
        cout << "\n=== MENU PETUGAS ===\n";
        cout << "1. Login Petugas\n";
        cout << "2. Tambah Petugas\n";
        cout << "3. Lihat Petugas\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                loginPetugas();
                break;
            case 2:
                tambahPetugas();
                break;
            case 3:
                lihatPetugas();
                break;
            case 0:
                cout << "Keluar...\n";
                break;
            default:
                cout << "Menu tidak valid!\n";
        }
    } while (pilih != 0);
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
        cout << i + 1 << ". " << dataanggota[i].nama << endl;
        cout << "   ID     : " << dataanggota[i].id_anggota << endl;
        cout << "   Alamat : " << dataanggota[i].alamat << endl;
        cout << "   Email  : " << dataanggota[i].email << endl;
        cout << "   Status : " << (dataanggota[i].status == 1 ? "Aktif" : "Nonaktif") << endl;
        cout << "-----------------------------------\n";
    }
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


// ============ BUKU ============

string generateIdBuku() {
    int urut = jumlahbuku + 1;
    string id = "";

    if (urut < 10) id = "00000" + to_string(urut);
    else if (urut < 100) id = "0000" + to_string(urut);
    else if (urut < 1000) id = "000" + to_string(urut);
    else if (urut < 10000) id = "00" + to_string(urut);
    else if (urut < 100000) id = "0" + to_string(urut);
    else id = to_string(urut);

    return id;
}


void tambahBuku() {
    cout << "\nTambah Buku\n";

    cin.ignore();
    databuku[jumlahbuku].id_buku = generateIdBuku();

    while (true) {
        cout << "ISBN (13 digit): ";
        getline(cin, databuku[jumlahbuku].isbn);

        if (databuku[jumlahbuku].isbn.length() != 13) {
            cout << "!! ISBN harus tepat 13 digit !!\n";
            continue;
        }

        bool valid = true;
        for (char c : databuku[jumlahbuku].isbn) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "!! ISBN hanya boleh angka !!\n";
            continue;
        }

        break;
    }

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
        cout << databuku[i].id_buku << " - " << databuku[i].judul << endl;
    }
}

void cariBuku() {
    cout << "\nCari Buku\n";
    cin.ignore();

    string keyword;
    cout << "Masukkan judul / ISBN / ID Buku yang dicari: ";
    getline(cin, keyword);

    bool found = false;

    for (int i = 0; i < jumlahbuku; i++) {
        if (databuku[i].judul == keyword ||
            databuku[i].isbn == keyword ||
            databuku[i].id_buku == keyword)
        {
            cout << "\n=== DATA BUKU DITEMUKAN ===\n";
            cout << "ID Buku      : " << databuku[i].id_buku << endl;
            cout << "ISBN         : " << databuku[i].isbn << endl;
            cout << "Judul        : " << databuku[i].judul << endl;
            cout << "Pengarang    : " << databuku[i].pengarang << endl;
            cout << "Penerbit     : " << databuku[i].penerbit << endl;
            cout << "Tahun Terbit : " << databuku[i].tahun_terbit << endl;
            cout << "Stok         : " << databuku[i].stok << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Buku tidak ditemukan.\n";
    }
}



void menuBuku() {
    int pilih;
    do {
        cout << "\n=== MENU BUKU ===\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Lihat Buku\n";
        cout << "3. Cari Buku\n";
        cout << "4. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) tambahBuku();
        else if (pilih == 2) lihatBuku();
        else if (pilih == 3) cariBuku();

    } while (pilih != 4);
}

// ======= MENU PEMINJAMAN =======

string generateIdPeminjaman() {
    int urut = jumlahpeminjaman + 1;
    string id = "";

    if (urut < 10) id = "P00000" + to_string(urut);
    else if (urut < 100) id = "P0000" + to_string(urut);
    else if (urut < 1000) id = "P000" + to_string(urut);
    else if (urut < 10000) id = "P00" + to_string(urut);
    else if (urut < 100000) id = "P0" + to_string(urut);
    else id = "P" + to_string(urut);

    return id;
}

string tambah7Hari(string tgl) {
    int d, m, y;
    sscanf(tgl.c_str(), "%d-%d-%d", &d, &m, &y);

    d += 7;
    if (d > 30) {
        d -= 30;
        m++;
    }
    if (m > 12) {
        m = 1;
        y++;
    }

    char buffer[20];
    sprintf(buffer, "%02d-%02d-%04d", d, m, y);
    return string(buffer);
}

int hitungDenda(string wajib, string aktual) {
    int d1, m1, y1;
    int d2, m2, y2;

    sscanf(wajib.c_str(), "%d-%d-%d", &d1, &m1, &y1);
    sscanf(aktual.c_str(), "%d-%d-%d", &d2, &m2, &y2);

    int hari1 = y1 * 365 + m1 * 30 + d1;
    int hari2 = y2 * 365 + m2 * 30 + d2;

    int terlambat = hari2 - hari1;
    if (terlambat <= 7) return 0;

    return (terlambat - 7) * 1000;
}

void tambahPeminjaman() {
    cout << "\n=== Tambah Peminjaman ===\n";

    cin.ignore();

    datapeminjaman[jumlahpeminjaman].id_peminjaman = generateIdPeminjaman();

    cout << "ID Anggota : ";
    getline(cin, datapeminjaman[jumlahpeminjaman].id_anggota);

    cout << "ID Buku    : ";
    getline(cin, datapeminjaman[jumlahpeminjaman].id_buku);

    cout << "Tanggal Pinjam (dd-mm-yyyy): ";
    getline(cin, datapeminjaman[jumlahpeminjaman].tanggal_pinjam);

    // AUTO TANGGAL KEMBALI
    datapeminjaman[jumlahpeminjaman].tanggal_kembali =
        tambah7Hari(datapeminjaman[jumlahpeminjaman].tanggal_pinjam);

    datapeminjaman[jumlahpeminjaman].status = 0; // belum kembali
    datapeminjaman[jumlahpeminjaman].denda = 0;

    cout << "Tanggal kembali otomatis: "
         << datapeminjaman[jumlahpeminjaman].tanggal_kembali << endl;

    jumlahpeminjaman++;
    cout << "Peminjaman berhasil ditambahkan.\n";
}

void cariPeminjaman() {
    cout << "\n=== Cari Peminjaman ===\n";

    cin.ignore();
    string keyword;
    cout << "Masukkan ID Peminjaman: ";
    getline(cin, keyword);

    bool found = false;

    for (int i = 0; i < jumlahpeminjaman; i++) {
        if (datapeminjaman[i].id_peminjaman == keyword) {

            cout << "\n=== DATA DITEMUKAN ===\n";
            cout << "ID Peminjaman : " << datapeminjaman[i].id_peminjaman << endl;
            cout << "ID Anggota    : " << datapeminjaman[i].id_anggota << endl;
            cout << "ID Buku       : " << datapeminjaman[i].id_buku << endl;
            cout << "Tanggal Pinjam: " << datapeminjaman[i].tanggal_pinjam << endl;
            cout << "Tanggal Kembali: " << datapeminjaman[i].tanggal_kembali << endl;
            cout << "Status        : "
                 << (datapeminjaman[i].status == 0 ? "Belum kembali" : "Sudah kembali")
                 << endl;
            cout << "Denda         : " << datapeminjaman[i].denda << endl;

            found = true;
        }
    }

    if (!found) cout << "Data tidak ditemukan.\n";
}

void listPeminjaman() {
    cout << "\n=== LIST PEMINJAMAN ===\n";

    if (jumlahpeminjaman == 0) {
        cout << "Belum ada data.\n";
        return;
    }

    for (int i = 0; i < jumlahpeminjaman; i++) {
        cout << datapeminjaman[i].id_peminjaman
             << " - " << datapeminjaman[i].id_anggota
             << " - " << datapeminjaman[i].id_buku << endl;
    }
}

void kembalikanBuku() {
    cout << "\n=== Kembalikan Buku ===\n";

    cin.ignore();
    string id;
    cout << "Masukkan ID Peminjaman: ";
    getline(cin, id);

    for (int i = 0; i < jumlahpeminjaman; i++) {
        if (datapeminjaman[i].id_peminjaman == id) {

            string tanggalDikembalikan;
            cout << "Tanggal Dikembalikan (dd-mm-yyyy): ";
            getline(cin, tanggalDikembalikan);

            datapeminjaman[i].denda =
                hitungDenda(datapeminjaman[i].tanggal_kembali, tanggalDikembalikan);

            datapeminjaman[i].status = 1;

            cout << "\n=== Buku Dikembalikan ===\n";
            cout << "Denda: " << datapeminjaman[i].denda << endl;

            return;
        }
    }

    cout << "ID tidak ditemukan.\n";
}

void menuPeminjaman() {
    int pilih;

    do {
        cout << "\n=== MENU PEMINJAMAN ===\n";
        cout << "1. Tambah Peminjaman\n";
        cout << "2. Lihat Peminjaman\n";
        cout << "3. Cari Peminjaman\n";
        cout << "4. Kembalikan Buku\n";
        cout << "5. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) tambahPeminjaman();
        else if (pilih == 2) listPeminjaman();
        else if (pilih == 3) cariPeminjaman();
        else if (pilih == 4) kembalikanBuku();

    } while (pilih != 5);
}


// ============ MENU UTAMA ============

void menuUtama() {
    int pilih;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Menu Anggota\n";
        cout << "2. Menu Buku\n";
        cout << "3. Menu Peminjaman\n";
        cout << "4. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) menuAnggota();
        else if (pilih == 2) menuBuku();
        else if (pilih == 3) menuPeminjaman();
        else if (pilih == 4) break;
    } while (true);
}

// ============ MAIN ============

int main() {
    AkunDefault();
    menuPetugas();
    menuUtama();
    return 0;
}

