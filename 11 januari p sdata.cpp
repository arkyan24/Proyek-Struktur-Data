#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct KTP {
    string nik;
    string nama;
    string alamat;
};

struct Barang {
    string kode;
    string tanggal;
};

struct Pembeli {
    string ktp;
    string waktu;
    string kodeBarang;
};

KTP dataKTP[100];
Barang gudang[100];
Pembeli antrianPembeli[100];
int jumlahKTP = 0;
int jumlahBarang = 0;
int jumlahPembeli = 0;

void loadDataKTP() {
    ifstream file("data_ktp.txt");
    if (file.is_open()) {
        while (file >> dataKTP[jumlahKTP].nik >> dataKTP[jumlahKTP].nama >> ws) {
            getline(file, dataKTP[jumlahKTP].alamat);
            jumlahKTP++;
        }
        file.close();
    }
}

bool signIn() {
    string inputNIK;
    cout << "========================\n";
    cout << "   Admin Sign In   \n";
    cout << "========================\n";
    cout << "Masukkan NIK: ";
    cin >> inputNIK;

    for (int i = 0; i < jumlahKTP; i++) {
        if (dataKTP[i].nik == inputNIK) {
            cout << "Selamat datang, " << dataKTP[i].nama << "!\n\n";
            return true;
        }
    }
    cout << "NIK tidak ditemukan!\n\n";
    return false;
}

void tambahBarang() {
    cout << "Masukkan kode barang: ";
    cin >> gudang[jumlahBarang].kode;
    cout << "Masukkan tanggal masuk (YYYY-MM-DD): ";
    cin >> gudang[jumlahBarang].tanggal;
    jumlahBarang++;
    cout << "Barang berhasil ditambahkan!\n";
}

void catatPembeli() {
    cout << "Masukkan NIK pembeli: ";
    cin >> antrianPembeli[jumlahPembeli].ktp;
    cout << "Masukkan waktu kedatangan (HH:MM): ";
    cin >> antrianPembeli[jumlahPembeli].waktu;
    cout << "Masukkan kode barang yang dibeli: ";
    cin >> antrianPembeli[jumlahPembeli].kodeBarang;
    jumlahPembeli++;
    cout << "Data pembeli berhasil dicatat!\n";
}

void cetakDaftarBarang() {
    cout << "Kode Barang       Tanggal Masuk\n";
    cout << "--------------------------------\n";
    for (int i = 0; i < jumlahBarang; i++) {
        cout << gudang[i].kode;
        for (int j = gudang[i].kode.length(); j < 15; j++) cout << " ";
        cout << gudang[i].tanggal << endl;
    }
}

void tampilkanPembeli() {
    cout << "NIK              Waktu     Kode Barang\n";
    cout << "----------------------------------------\n";
    for (int i = 0; i < jumlahPembeli; i++) {
        cout << antrianPembeli[i].ktp;
        for (int j = antrianPembeli[i].ktp.length(); j < 15; j++) cout << " ";
        cout << antrianPembeli[i].waktu;
        for (int j = antrianPembeli[i].waktu.length(); j < 10; j++) cout << " ";
        cout << antrianPembeli[i].kodeBarang << endl;
    }
}

void sortPembeliByWaktu() {
    for (int i = 0; i < jumlahPembeli - 1; i++) {
        for (int j = 0; j < jumlahPembeli - i - 1; j++) {
            if (antrianPembeli[j].waktu > antrianPembeli[j + 1].waktu) {
                Pembeli temp = antrianPembeli[j];
                antrianPembeli[j] = antrianPembeli[j + 1];
                antrianPembeli[j + 1] = temp;
            }
        }
    }
}

void layaniPembeli() {
    if (jumlahPembeli == 0) {
        cout << "Tidak ada pembeli dalam antrian!\n";
        return;
    }

    sortPembeliByWaktu();

    cout << "Melayani pembeli dengan NIK: " << antrianPembeli[0].ktp << endl;
    cout << "Waktu kedatangan: " << antrianPembeli[0].waktu << endl;
    cout << "Kode barang: " << antrianPembeli[0].kodeBarang << endl;

    for (int i = 1; i < jumlahPembeli; i++) {
        antrianPembeli[i - 1] = antrianPembeli[i];
    }
    jumlahPembeli--;
    cout << "Pembeli telah dilayani!\n";
}

int main() {
    loadDataKTP();

    if (!signIn()) {
        return 0;
    }

    int pilihan;
    do {
        cout << "========================\n";
        cout << "       MENU UTAMA       \n";
        cout << "========================\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Catat Pembeli\n";
        cout << "3. Cetak Daftar Barang\n";
        cout << "4. Tampilkan Pembeli\n";
        cout << "5. Layani Pembeli\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                catatPembeli();
                break;
            case 3:
                cetakDaftarBarang();
                break;
            case 4:
                tampilkanPembeli();
                break;
            case 5:
                layaniPembeli();
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

        cout << endl;
    } while (pilihan != 0);

    return 0;
}

