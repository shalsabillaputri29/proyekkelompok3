#include <iostream>
#include <fstream>
using namespace std;

struct nilai {
    float Mtk;
    float BIn;
    float Big;
    float IPA;
};

struct siswa {
    string nama;
    string NISN;
    string jurusan;
    nilai Nilai;
    float nilaiAkhir;
};

void tambahDataSiswa() {
    int jumlah;
    cout << "Masukkan jumlah siswa: ";
    cin >> jumlah;
    cin.ignore();

    ofstream file("siswaa.txt", ios::app);
    if (!file) {
        cout << "Gagal membuka file!\n";
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        siswa s;
        cout << "\n=== Data siswa ke-" << i + 1 << " ===" << endl;
        cout << "Masukkan NISN       : ";
        getline(cin, s.NISN);
        cout << "Masukkan Nama       : ";
        getline(cin, s.nama);
        cout << "Masukkan Jurusan    : ";
        getline(cin, s.jurusan);
        cout << "Nilai Matematika    : ";
        cin >> s.Nilai.Mtk;
        cout << "Nilai IPA           : ";
        cin >> s.Nilai.IPA;
        cout << "Nilai B. Indonesia  : ";
        cin >> s.Nilai.BIn;
        cout << "Nilai B. Inggris    : ";
        cin >> s.Nilai.Big;
        cin.ignore();

        s.nilaiAkhir = (0.4 * s.Nilai.Mtk) + (0.3 * s.Nilai.IPA) + (0.2 * s.Nilai.BIn) + (0.1 * s.Nilai.Big);

        // tulis ke file (urutan sama kayak yang dibaca)
        file << s.NISN << " " << s.nama << " " << s.jurusan << " "
             << s.Nilai.Mtk << " " << s.Nilai.BIn << " " << s.Nilai.Big
             << " " << s.Nilai.IPA << " " << s.nilaiAkhir << endl;

        cout << "\n--- Data Siswa ---" << endl;
        cout << "NISN          : " << s.NISN << endl;
        cout << "Nama          : " << s.nama << endl;
        cout << "Jurusan       : " << s.jurusan << endl;
        cout << "Matematika    : " << s.Nilai.Mtk << endl;
        cout << "IPA           : " << s.Nilai.IPA << endl;
        cout << "B. Indonesia  : " << s.Nilai.BIn << endl;
        cout << "B. Inggris    : " << s.Nilai.Big << endl;
        cout << "Nilai Akhir   : " << s.nilaiAkhir << endl;
    }

    file.close();
    cout << "\nData berhasil disimpan ke siswa.txt\n";
}

void tampilDataSiswa() {
    ifstream file("siswaa.txt");
    if (!file) {
        cout << "Belum ada data siswa.\n";
        return;
    }

    siswa s;
    cout << "\n===== DAFTAR DATA SISWA =====\n";
    while (file >> s.NISN >> s.nama >> s.jurusan
                >> s.Nilai.Mtk >> s.Nilai.BIn >> s.Nilai.Big
                >> s.Nilai.IPA >> s.nilaiAkhir) {
        cout << "NISN: " << s.NISN
             << "\nNama: " << s.nama
             << "\nJurusan: " << s.jurusan
             << "\nMatematika: " << s.Nilai.Mtk
             << "\nIPA: " << s.Nilai.IPA
             << "\nB. Indonesia: " << s.Nilai.BIn
             << "\nB. Inggris: " << s.Nilai.Big
             << "\nNilai Akhir: " << s.nilaiAkhir << "\n\n";
    }

    file.close();
}

void cariSiswa() {
    ifstream file("siswaa.txt");
    if (!file) {
        cout << "File data tidak ditemukan.\n";
        return;
    }

    string cariNISN;
    siswa s;
    bool ketemu = false;

    cout << "Masukkan NISN yang dicari: ";
    getline(cin, cariNISN);

    while (file >> s.NISN >> s.nama >> s.jurusan
                >> s.Nilai.Mtk >> s.Nilai.BIn >> s.Nilai.Big
                >> s.Nilai.IPA >> s.nilaiAkhir) {
        if (s.NISN == cariNISN) {
            cout << "\nData ditemukan!\n";
            cout << "Nama: " << s.nama
                 << "\nJurusan: " << s.jurusan
                 << "\nNilai Akhir: " << s.nilaiAkhir << endl;
            ketemu = true;
            break;
        }
    }

    if (!ketemu)
        cout << "Data tidak ditemukan.\n";

    file.close();
}

void ranking() {
    ifstream file("siswaa.txt");
    siswa data[100];
    int n = 0;

    if (!file) {
        cout << "Belum ada data siswa untuk diranking.\n";
        return;
    }

    while (file >> data[n].NISN >> data[n].nama >> data[n].jurusan
                >> data[n].Nilai.Mtk >> data[n].Nilai.BIn >> data[n].Nilai.Big
                >> data[n].Nilai.IPA >> data[n].nilaiAkhir) {
        n++;
    }
    file.close();

    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j].nilaiAkhir < data[j + 1].nilaiAkhir) {
                siswa temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    ofstream out("rankingg.txt");
    out << "===== RANKING SISWA =====\n";
    out << "RANK\tNISN\tNAMA\tNILAI AKHIR\n";
    for (int i = 0; i < n; i++) {
        out << i + 1 << "\t" << data[i].NISN << "\t"
            << data[i].nama << "\t" << data[i].nilaiAkhir << endl;
    }
    out.close();

    cout << "\nRanking berhasil diperbarui. Lihat file ranking.txt\n";
}

int main() {
    //iputimutttttttttttt
    //wildansep
    int pilih;
    do {
        cout << "\n===== MENU DATA SISWA =====\n";
        cout << "1. Tambah Data Siswa\n";
        cout << "2. Tampilkan Data Siswa\n";
        cout << "3. Cari Data Siswa (berdasarkan NISN)\n";
        cout << "4. Tampilkan Ranking Siswa\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: tambahDataSiswa(); ranking(); break;
            case 2: tampilDataSiswa(); break;
            case 3: cariSiswa(); break;
            case 4: ranking(); break;
            case 5: cout << "Keluar dari program...\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 5);

    //wildanz collab

    return 0;
}



