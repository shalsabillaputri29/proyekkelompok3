#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> 
using namespace std;

// ========== STRUCT ==========
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
    string tanggal_pinjam;   // dd-mm-yyyy
    string tanggal_kembali;  // dd-mm-yyyy
    int status;              // 1 = belum kembali, 0 = sudah kembali
    int denda;
};

struct Petugas {
    string id_petugas;
    string username;
    string password;
    string nama;
};

// ========== DATABASE ==========
Anggota dataanggota[200];
Buku databuku[500];
Petugas datapetugas[100];
Peminjaman datapeminjaman[500];

int jumlahanggota = 0;
int jumlahbuku = 0;
int jumlahpetugas = 0;
int jumlahpeminjaman = 0;

// tanggal hari ini (diisi petugas setelah login)
string currentDate = "";

// ========== PROTOTYPE ==========
void loadAll();
void saveAll();

void menuUtama();
void menuPetugas();
void menuAnggota();
void menuBuku();
void menuPeminjaman();

// Petugas
string generateIdPetugas();
void loadPetugas();
void savePetugas();
void AkunDefault();
void tambahPetugas();
bool loginPetugas();
void lihatPetugas();

// Anggota
string generateKodeAnggota(string tahun, string bulan, string tanggal);
void loadAnggota();
void saveAnggota();
void tambahAnggota();
void lihatAnggota();

// Buku
string generateIdBuku();
void loadBuku();
void saveBuku();
void tambahBuku();
void lihatBuku();
int findBukuIndexById(const string &id);

// Peminjaman
string generateIdPeminjaman();
string tambah7Hari(const string &tgl); // dd-mm-yyyy, feb=28
int dateToDays(int d, int m, int y);
int hitungDenda(const string &batas, const string &aktual);
void loadPeminjaman();
void savePeminjaman();
void tambahPeminjaman();
void cariPeminjaman();
void listPeminjaman();
void kembalikanBuku();
bool anggotaPunyaPinjamanAktif(const string &id_anggota);
int findPeminjamanIndexById(const string &id);
int hariDalamBulan(int bulan);
int hariDalamBulan(int bulan) {
    switch (bulan) {
        case 1: return 31;
        case 2: return 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
    }
    return 30;
}

int dateToDays(int d, int m, int y) {
    return y * 365 + m * 30 + d;
}

string tambah7Hari(const string &tgl) {
    int d, m, y;
    if (sscanf(tgl.c_str(), "%d-%d-%d", &d, &m, &y) != 3) return tgl;
    d += 7;
    int mdays = hariDalamBulan(m);
    if (d > mdays) {
        d -= mdays;
        m++;
        if (m > 12) { m = 1; y++; }
    }
    char buf[16];
    sprintf(buf, "%02d-%02d-%04d", d, m, y);
    return string(buf);
}

int hitungDenda(const string &batas, const string &aktual) {
    int d1,m1,y1,d2,m2,y2;
    if (sscanf(batas.c_str(), "%d-%d-%d", &d1,&m1,&y1) != 3) return 0;
    if (sscanf(aktual.c_str(), "%d-%d-%d", &d2,&m2,&y2) != 3) return 0;
    int hari1 = dateToDays(d1,m1,y1);
    int hari2 = dateToDays(d2,m2,y2);
    int selisih = hari2 - hari1;
    if (selisih <= 0) return 0;
    if (selisih <= 7) return 0; // bebas denda dalam 7 hari
    return (selisih - 7) * 1000;
}

// ========== PETUGAS ==========
string generateIdPetugas() {
    int urut = jumlahpetugas + 1;
    string id = to_string(urut);
    while (id.length() < 6) id = "0" + id;
    return id;
}

void loadPetugas() {
    ifstream f("petugas.txt");
    if (!f.is_open()) return;
    jumlahpetugas = 0;
    string line;
    while (getline(f,line)) {
        if (line.rfind("ID:",0) == 0) {
            datapetugas[jumlahpetugas].id_petugas = line.substr(4);
            getline(f,line); datapetugas[jumlahpetugas].username = line.substr(line.find(":") + 2);
            getline(f,line); datapetugas[jumlahpetugas].password = line.substr(line.find(":") + 2);
            getline(f,line); datapetugas[jumlahpetugas].nama = line.substr(6);
            getline(f,line); // ---
            jumlahpetugas++;
        }
    }
    f.close();
}

void savePetugas() {
    ofstream f("petugas.txt");
    for (int i=0;i<jumlahpetugas;i++){
        f << "ID: " << datapetugas[i].id_petugas << "\n";
        f << "Username: " << datapetugas[i].username << "\n";
        f << "Password: " << datapetugas[i].password << "\n";
        f << "Nama: " << datapetugas[i].nama << "\n";
        f << "---\n";
    }
    f.close();
}

void AkunDefault() {
    if (jumlahpetugas == 0) {
        datapetugas[0].id_petugas = "000001";
        datapetugas[0].username = "etmin";
        datapetugas[0].password = "etmin123";
        datapetugas[0].nama = "Administrator";
        jumlahpetugas = 1;
        savePetugas();
    }
}

void tambahPetugas() {
    system("cls");
    cout << "✨ TAMBAH PETUGAS ✨\n";
    string user, pass, nama;
    datapetugas[jumlahpetugas].id_petugas = generateIdPetugas();
    cout << "Username: "; cin >> user;
    cout << "Password: "; cin >> pass;
    cin.ignore();
    cout << "Nama Petugas: "; getline(cin, nama);
    datapetugas[jumlahpetugas].username = user;
    datapetugas[jumlahpetugas].password = pass;
    datapetugas[jumlahpetugas].nama = nama;
    jumlahpetugas++;
    savePetugas();
    cout << "Sukses. ID: " << datapetugas[jumlahpetugas-1].id_petugas << "\n";
}

bool loginPetugas() {
    string u,p;
    system("cls");
    cout << "🔐 LOGIN PETUGAS 🔐\n";
    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;
    for (int i=0;i<jumlahpetugas;i++){
        if (datapetugas[i].username == u && datapetugas[i].password == p) {
            cout << "Login berhasil. Halo, " << datapetugas[i].nama << "!\n";
            return true;
        }
    }
    cout << "Login gagal.\n";
    return false;
}

void lihatPetugas() {
    system("cls");
    cout << "👥 DATA PETUGAS 👥\n";
    if (jumlahpetugas==0) { cout << "Belum ada data.\n"; return; }
    for (int i=0;i<jumlahpetugas;i++){
        cout << "ID: " << datapetugas[i].id_petugas << "\n";
        cout << "Username: " << datapetugas[i].username << "\n";
        cout << "Nama: " << datapetugas[i].nama << "\n";
        cout << "-----------------\n";
    }
}

// ========== ANGGOTA ==========
string generateKodeAnggota(string tahun, string bulan, string tanggal) {
    string dasar = tahun + bulan + tanggal;
    int hitung = 0;
    for (int i=0;i<jumlahanggota;i++){
        if (dataanggota[i].id_anggota.substr(0,8) == dasar) hitung++;
    }
    hitung++;
    string urut;
    if (hitung < 10) urut = "00" + to_string(hitung);
    else if (hitung < 100) urut = "0" + to_string(hitung);
    else urut = to_string(hitung);
    return dasar + urut;
}

void loadAnggota() {
    ifstream f("anggota.txt");
    if (!f.is_open()) return;
    jumlahanggota = 0;
    string line;
    while (getline(f,line)) {
        if (line.rfind("ID:",0) == 0) {
            dataanggota[jumlahanggota].id_anggota = line.substr(4);
            getline(f,line); dataanggota[jumlahanggota].kode_anggota = line.substr(6);
            getline(f,line); dataanggota[jumlahanggota].nama = line.substr(6);
            getline(f,line); dataanggota[jumlahanggota].alamat = line.substr(8);
            getline(f,line); dataanggota[jumlahanggota].email = line.substr(7);
            getline(f,line); dataanggota[jumlahanggota].status = stoi(line.substr(8));
            getline(f,line); // ---
            jumlahanggota++;
        }
    }
    f.close();
}

void saveAnggota() {
    ofstream f("anggota.txt");
    for (int i=0;i<jumlahanggota;i++){
        f << "ID: " << dataanggota[i].id_anggota << "\n";
        f << "Kode: " << dataanggota[i].kode_anggota << "\n";
        f << "Nama: " << dataanggota[i].nama << "\n";
        f << "Alamat: " << dataanggota[i].alamat << "\n";
        f << "Email: " << dataanggota[i].email << "\n";
        f << "Status: " << dataanggota[i].status << "\n";
        f << "---\n";
    }
    f.close();
}

void tambahAnggota() {
    system("cls");
    cout << "🆕 TAMBAH ANGGOTA 🆕\n";
    Anggota a;
    cin.ignore();
    cout << "Nama: "; getline(cin, a.nama);
    cout << "Alamat: "; getline(cin, a.alamat);
    cout << "Email: "; getline(cin, a.email);
    string tahun,bulan,tanggal;
    cout << "Tahun Lahir (YYYY): "; cin >> tahun;
    cout << "Bulan Lahir (MM): "; cin >> bulan;
    cout << "Tanggal Lahir (DD): "; cin >> tanggal;
    a.id_anggota = generateKodeAnggota(tahun,bulan,tanggal);
    a.kode_anggota = a.id_anggota;
    a.status = 1;
    dataanggota[jumlahanggota] = a;
    jumlahanggota++;
    saveAnggota();
    cout << "Anggota terdaftar. Kode: " << a.kode_anggota << "\n";
}

void lihatAnggota() {
    system("cls");
    cout << "📇 DATA ANGGOTA 📇\n";
    if (jumlahanggota==0){ cout<<"Belum ada anggota.\n"; return; }
    for (int i=0;i<jumlahanggota;i++){
        cout << i+1 << ". " << dataanggota[i].nama << "\n";
        cout << "   ID: " << dataanggota[i].id_anggota << "\n";
        cout << "   Alamat: " << dataanggota[i].alamat << "\n";
        cout << "   Email: " << dataanggota[i].email << "\n";
        cout << "   Status: " << (dataanggota[i].status==1 ? "Aktif":"Nonaktif") << "\n";
        cout << "-----------------\n";
    }
}

// ========== BUKU ==========
string generateIdBuku() {
    int urut = jumlahbuku + 1;
    string id = "";
    if (urut < 10) id = "00000" + to_string(urut);
    else if (urut < 100) id = "0000" + to_string(urut);
    else if (urut < 1000) id = "000" + to_string(urut);
    else if (urut < 10000) id = "00" + to_string(urut);
    else id = to_string(urut);
    return id;
}

void loadBuku() {
    ifstream f("buku.txt");
    if (!f.is_open()) return;
    jumlahbuku = 0;
    string line;
    while (getline(f,line)) {
        if (line.rfind("ID:",0) == 0) {
            databuku[jumlahbuku].id_buku = line.substr(4);
            getline(f,line); databuku[jumlahbuku].isbn = line.substr(6);
            getline(f,line); databuku[jumlahbuku].judul = line.substr(7);
            getline(f,line); databuku[jumlahbuku].pengarang = line.substr(11);
            getline(f,line); databuku[jumlahbuku].penerbit = line.substr(10);
            getline(f,line); databuku[jumlahbuku].tahun_terbit = stoi(line.substr(7));
            getline(f,line); databuku[jumlahbuku].stok = stoi(line.substr(6));
            getline(f,line); // ---
            jumlahbuku++;
        }
    }
    f.close();
}

void saveBuku() {
    ofstream f("buku.txt");
    for (int i=0;i<jumlahbuku;i++){
        f << "ID: " << databuku[i].id_buku << "\n";
        f << "ISBN: " << databuku[i].isbn << "\n";
        f << "Judul: " << databuku[i].judul << "\n";
        f << "Pengarang: " << databuku[i].pengarang << "\n";
        f << "Penerbit: " << databuku[i].penerbit << "\n";
        f << "Tahun: " << databuku[i].tahun_terbit << "\n";
        f << "Stok: " << databuku[i].stok << "\n";
        f << "---\n";
    }
    f.close();
}

void tambahBuku() {
    system("cls");
    cout << "📚 TAMBAH BUKU 📚\n";
    Buku b;
    cin.ignore();
    b.id_buku = generateIdBuku();
    while (true) {
        cout << "ISBN (13 digit): "; getline(cin, b.isbn);
        if (b.isbn.length() != 13) { cout << "ISBN harus 13 digit!\n"; continue; }
        bool ok = true;
        for (char c : b.isbn) if (!isdigit(c)) ok = false;
        if (!ok) { cout << "ISBN harus angka!\n"; continue; }
        break;
    }
    cout << "Judul: "; getline(cin, b.judul);
    cout << "Pengarang: "; getline(cin, b.pengarang);
    cout << "Penerbit: "; getline(cin, b.penerbit);
    cout << "Tahun terbit: "; cin >> b.tahun_terbit;
    cout << "Stok: "; cin >> b.stok;
    databuku[jumlahbuku] = b;
    jumlahbuku++;
    saveBuku();
    cout << "Buku ditambahkan. ID: " << databuku[jumlahbuku-1].id_buku << "\n";
}

void lihatBuku() {
    system("cls");
    cout << "📚 DATA BUKU 📚\n";
    if (jumlahbuku==0){ cout<<"Belum ada buku.\n"; return; }
    for (int i=0;i<jumlahbuku;i++){
        cout << databuku[i].id_buku << " - " << databuku[i].judul << " (Stok: " << databuku[i].stok << ")\n";
    }
}

int findBukuIndexById(const string &id) {
    for (int i=0;i<jumlahbuku;i++) if (databuku[i].id_buku == id) return i;
    return -1;
}

// ========== PEMINJAMAN ==========
string generateIdPeminjaman() {
    int urut = jumlahpeminjaman + 1;
    string id = "";
    if (urut < 10) id = "00000" + to_string(urut);
    else if (urut < 100) id = "0000" + to_string(urut);
    else if (urut < 1000) id = "000" + to_string(urut);
    else if (urut < 10000) id = "00" + to_string(urut);
    else id = to_string(urut);
    return id;
}

void loadPeminjaman() {
    ifstream f("peminjaman.txt");
    if (!f.is_open()) return;
    jumlahpeminjaman = 0;
    string line;
    while (getline(f,line)) {
        if (line.rfind("ID:",0) == 0) {
            datapeminjaman[jumlahpeminjaman].id_peminjaman = line.substr(4);
            getline(f,line); datapeminjaman[jumlahpeminjaman].id_anggota = line.substr(9);
            getline(f,line); datapeminjaman[jumlahpeminjaman].id_buku = line.substr(6);
            getline(f,line); datapeminjaman[jumlahpeminjaman].tanggal_pinjam = line.substr(8);
            getline(f,line); datapeminjaman[jumlahpeminjaman].tanggal_kembali = line.substr(9);
            getline(f,line); datapeminjaman[jumlahpeminjaman].status = stoi(line.substr(8));
            getline(f,line); datapeminjaman[jumlahpeminjaman].denda = stoi(line.substr(7));
            getline(f,line); // ---
            jumlahpeminjaman++;
        }
    }
    f.close();
}

void savePeminjaman() {
    ofstream f("peminjaman.txt");
    for (int i=0;i<jumlahpeminjaman;i++){
        f << "ID: " << datapeminjaman[i].id_peminjaman << "\n";
        f << "Anggota: " << datapeminjaman[i].id_anggota << "\n";
        f << "Buku: " << datapeminjaman[i].id_buku << "\n";
        f << "Pinjam: " << datapeminjaman[i].tanggal_pinjam << "\n";
        f << "Kembali: " << datapeminjaman[i].tanggal_kembali << "\n";
        f << "Status: " << datapeminjaman[i].status << "\n";
        f << "Denda: " << datapeminjaman[i].denda << "\n";
        f << "---\n";
    }
    f.close();
}

bool anggotaPunyaPinjamanAktif(const string &id_anggota) {
    for (int i=0;i<jumlahpeminjaman;i++) {
        if (datapeminjaman[i].id_anggota == id_anggota && datapeminjaman[i].status == 1)
            return true;
    }
    return false;
}

int findPeminjamanIndexById(const string &id) {
    for (int i=0;i<jumlahpeminjaman;i++) if (datapeminjaman[i].id_peminjaman == id) return i;
    return -1;
}

void tambahPeminjaman() {
    system("cls");
    cout << "📥 TAMBAH PEMINJAMAN 📥\n";
    if (currentDate == "") {
        cout << "Tanggal hari ini belum di-set. Kembali ke menu utama dan set tanggal.\n";
        return;
    }

    string idanggota, idbuku;
    cin.ignore();
    cout << "ID Anggota: "; getline(cin, idanggota);
    // cek anggota ada?
    bool adaAng = false;
    for (int i=0;i<jumlahanggota;i++) if (dataanggota[i].id_anggota == idanggota) { adaAng=true; break; }
    if (!adaAng) { cout << "Anggota tidak ditemukan.\n"; return; }

    // cek apakah anggota masih punya pinjaman aktif
    if (anggotaPunyaPinjamanAktif(idanggota)) {
        cout << "Anggota masih punya pinjaman aktif. Tidak bisa pinjam lagi.\n";
        return;
    }

    cout << "ID Buku: "; getline(cin, idbuku);
    int idx = findBukuIndexById(idbuku);
    if (idx == -1) { cout << "Buku tidak ditemukan.\n"; return; }
    if (databuku[idx].stok <= 0) { cout << "Stok buku habis.\n"; return; }

    // kurangi stok
    databuku[idx].stok--;
    saveBuku();

    // buat record peminjaman
    Peminjaman p;
    p.id_peminjaman = generateIdPeminjaman();
    p.id_anggota = idanggota;
    p.id_buku = idbuku;
    p.tanggal_pinjam = currentDate; // otomatis
    p.tanggal_kembali = tambah7Hari(p.tanggal_pinjam);
    p.status = 1; // belum kembali
    p.denda = 0;

    datapeminjaman[jumlahpeminjaman] = p;
    jumlahpeminjaman++;
    savePeminjaman();

    cout << "Peminjaman dicatat. ID: " << p.id_peminjaman << "\n";
    cout << "Pinjam: " << p.tanggal_pinjam << " | Kembali: " << p.tanggal_kembali << "\n";
}

void cariPeminjaman() {
    system("cls");
    cout << "🔎 CARI PEMINJAMAN 🔎\n";
    cin.ignore();
    string key;
    cout << "Masukkan ID Peminjaman: "; getline(cin, key);
    bool found = false;
    for (int i=0;i<jumlahpeminjaman;i++){
        if (datapeminjaman[i].id_peminjaman == key) {
            cout << "ID: " << datapeminjaman[i].id_peminjaman << "\n";
            cout << "Anggota: " << datapeminjaman[i].id_anggota << "\n";
            cout << "Buku: " << datapeminjaman[i].id_buku << "\n";
            cout << "Pinjam: " << datapeminjaman[i].tanggal_pinjam << "\n";
            cout << "Kembali: " << datapeminjaman[i].tanggal_kembali << "\n";
            cout << "Status: " << (datapeminjaman[i].status==1 ? "Belum kembali":"Sudah kembali") << "\n";
            cout << "Denda: " << datapeminjaman[i].denda << "\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Data tidak ditemukan.\n";
}

void listPeminjaman() {
    system("cls");
    cout << "📜 LIST PEMINJAMAN 📜\n";
    if (jumlahpeminjaman==0) { cout << "Belum ada data peminjaman.\n"; return; }
    for (int i=0;i<jumlahpeminjaman;i++){
        cout << "ID: " << datapeminjaman[i].id_peminjaman << "\n";
        cout << "Anggota: " << datapeminjaman[i].id_anggota << "\n";
        cout << "Buku: " << datapeminjaman[i].id_buku << "\n";
        cout << "Pinjam: " << datapeminjaman[i].tanggal_pinjam << "\n";
        cout << "Kembali: " << datapeminjaman[i].tanggal_kembali << "\n";
        cout << "Status: " << (datapeminjaman[i].status==1 ? "Belum kembali":"Sudah kembali") << "\n";
        cout << "Denda: " << datapeminjaman[i].denda << "\n";
        cout << "------------------------\n";
    }
}

void kembalikanBuku() {
    system("cls");
    cout << "📤 PENGEMBALIAN BUKU 📤\n";
    cin.ignore();
    string id;
    cout << "Masukkan ID Peminjaman: "; getline(cin, id);
    int idx = findPeminjamanIndexById(id);
    if (idx == -1) { cout << "ID tidak ditemukan.\n"; return; }
    if (datapeminjaman[idx].status == 0) { cout << "Buku sudah dikembalikan sebelumnya.\n"; return; }

    string tglk;
    cout << "Tanggal Dikembalikan (dd-mm-yyyy): "; getline(cin, tglk);

    int denda = hitungDenda(datapeminjaman[idx].tanggal_kembali, tglk);
    datapeminjaman[idx].denda = denda;
    datapeminjaman[idx].status = 0; // sudah kembali
    savePeminjaman();

    // kembalikan stok buku
    int idbidx = findBukuIndexById(datapeminjaman[idx].id_buku);
    if (idbidx != -1) {
        databuku[idbidx].stok++;
        saveBuku();
    }

    cout << "Pengembalian tercatat. Denda: " << denda << "\n";
}

// ========== LOAD / SAVE ALL ==========
void loadAll() {
    loadPetugas();
    loadAnggota();
    loadBuku();
    loadPeminjaman();
}

void saveAll() {
    savePetugas();
    saveAnggota();
    saveBuku();
    savePeminjaman();
}

// ========== MENUS ==========

void menuPetugas() {
    while (true) {
        system("cls");
        cout << "📚 — perpustakaan digital — 📚\n";
        cout << "1️⃣  Login Petugas\n";
        cout << "2️⃣  Tambah Petugas\n";
        cout << "3️⃣  Lihat Petugas\n";
        cout << "4️⃣  Set Tanggal Hari Ini\n";
        cout << "0️⃣  Kembali\n";
        cout << "Pilih: ";
        int p; cin >> p;
        if (p==1) {
            if (loginPetugas()) {
                // setelah login, minta set tanggal hari ini
                cin.ignore();
                cout << "Masukkan tanggal hari ini (dd-mm-yyyy) : ";
                getline(cin, currentDate);
                return; // kembali ke main untuk masuk dashboard
            } else {
                cout << "Tekan enter untuk kembali..."; cin.ignore(); cin.get();
            }
        } else if (p==2) tambahPetugas();
        else if (p==3) { lihatPetugas(); cout << "Tekan enter..."; cin.ignore(); cin.get(); }
        else if (p==4) { cin.ignore(); cout << "Masukkan tanggal hari ini (dd-mm-yyyy) : "; getline(cin, currentDate); }
        else if (p==0) return;
        else { cout << "Pilihan tidak valid.\n"; }
    }
}

void menuAnggota() {
    while (true) {
        system("cls");
        cout << "1. Tambah Anggota\n2. Lihat Anggota\n0. Kembali\nPilih: ";
        int p; cin >> p;
        if (p==1) tambahAnggota();
        else if (p==2) { lihatAnggota(); cout << "Tekan enter..."; cin.ignore(); cin.get(); }
        else if (p==0) return;
    }
}

void menuBuku() {
    while (true) {
        system("cls");
        cout << "1. Tambah Buku\n2. Lihat Buku\n0. Kembali\nPilih: ";
        int p; cin >> p;
        if (p==1) tambahBuku();
        else if (p==2) { lihatBuku(); cout << "Tekan enter..."; cin.ignore(); cin.get(); }
        else if (p==0) return;
    }
}

void menuPeminjaman() {
    while (true) {
        system("cls");
        cout << "1. Pinjam Buku\n2. List Peminjaman\n3. Cari Peminjaman\n4. Kembalikan Buku\n0. Kembali\nPilih: ";
        int p; cin >> p;
        if (p==1) { tambahPeminjaman(); cout << "Tekan enter..."; cin.ignore(); cin.get(); }
        else if (p==2) { listPeminjaman(); cout << "Tekan enter..."; cin.ignore(); cin.get(); }
        else if (p==3) { cariPeminjaman(); cout << "Tekan enter..."; cin.ignore(); cin.get(); }
        else if (p==4) { kembalikanBuku(); cout << "Tekan enter..."; cin.ignore(); cin.get(); }
        else if (p==0) return;
    }
}

void menuUtama() {
    while (true) {
        system("cls");
        cout << "📚 — perpustakaan digital — 📚\n";
        cout << "1️⃣  petugas\n";
        cout << "2️⃣  anggota\n";
        cout << "3️⃣  buku\n";
        cout << "4️⃣  pinjam\n";
        cout << "5️⃣  kembali\n";
        cout << "6️⃣  simpan semua\n";
        cout << "7️⃣  keluar\n";
        cout << "Pilih: ";
        int p; cin >> p;
        if (p==1) menuPetugas();
        else if (p==2) menuAnggota();
        else if (p==3) menuBuku();
        else if (p==4) menuPeminjaman();
        else if (p==5) { kembalikanBuku(); cout << "Tekan enter..."; cin.ignore(); cin.get(); }
        else if (p==6) { saveAll(); cout << "Semua data disimpan.\n"; cout << "Tekan enter..."; cin.ignore(); cin.get(); }
        else if (p==7) { saveAll(); break; }
        else { cout << "Pilihan tidak valid.\n"; }
    }
}

// ========== MAIN ==========
int main() {
    system("chcp 65001 >nul");
    loadAll();
    // pastikan ada akun default kalau file kosong
    AkunDefault();

    // login wajib sebelum dashboard
    while (true) {
        cout << "🔔 Akses sistem perpustakaan (login petugas wajib)\n";
        cout << "1. Menu Petugas (login)\n2. Keluar\nPilih: ";
        int p; cin >> p;
        if (p==1) {
            menuPetugas();
            if (currentDate != "") break; // jika login sukses & tanggal di-set, lanjut
        } else {
            cout << "Keluar...\n";
            return 0;
        }
    }

    // setelah login & set tanggal, masuk menu utama
    menuUtama();
    cout << "Terima kasih. Program selesai.\n";
    return 0;
}
