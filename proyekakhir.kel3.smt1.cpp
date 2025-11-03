#include <iostream>
using namespace std;

struct Buku {
    char id_buku[10];
    char isbn[20];
    char judul[50];
    char pengarang[30];
    char penerbit[30];
    int tahun_terbit;
    int stok;
};

Buku data_buku[50]; 
int jumlah_buku = 0;


void tambahBuku() {
    cout << "\n=== Tambah Buku ===\n";
    cout << "ID Buku       : ";
    cin >> data_buku[jumlah_buku].id_buku;
    cout << "ISBN          : ";
    cin >> data_buku[jumlah_buku].isbn;
    cout << "Judul         : ";
    cin.ignore(); // biar bisa input spasi di judul
    cin.getline(data_buku[jumlah_buku].judul, 50);
    cout << "Pengarang     : ";
    cin.getline(data_buku[jumlah_buku].pengarang, 30);
    cout << "Penerbit      : ";
    cin.getline(data_buku[jumlah_buku].penerbit, 30);
    cout << "Tahun Terbit  : ";
    cin >> data_buku[jumlah_buku].tahun_terbit;
    cout << "Stok          : ";
    cin >> data_buku[jumlah_buku].stok;

    jumlah_buku++;
    cout << ">> Buku berhasil ditambahkan!\n";
}

void tampilBuku() {
    cout << "\n=== Daftar Buku ===\n";
    if (jumlah_buku == 0) {
        cout << "(Belum ada data buku)\n";
    } else {
        for (int i = 0; i < jumlah_buku; i++) {
            cout << i + 1 << ". " << data_buku[i].judul
                 << " | ISBN: " << data_buku[i].isbn
                 << " | Stok: " << data_buku[i].stok << endl;
        }
    }



    return ;
}
