#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

struct Transaksi {
    string tanggal;
    string namaPenyewa;
    int kamar;
    int jumlah;
    string metode;
    string status;
};

// Maksimal jumlah transaksi yang dapat dicatat
const int MAX_TRANSAKSI = 100;
Transaksi riwayatTransaksi[MAX_TRANSAKSI];
int jumlahTransaksi = 0;

// =============================================
// FUNGSI VALIDASI INPUT STATUS PEMBAYARAN BARU
// =============================================
void validasiInputStatus(string &status) {
    bool valid = false;
    while (!valid) {
        cout << "Status pembayaran (Lunas/Belum): ";
        cin >> status;
        
        // Konversi ke huruf kapital untuk mempermudah validasi
        for (char &c : status) {
            c = toupper(c);
        }
        
        if (status == "LUNAS" || status == "BELUM") {
            valid = true;
            // Kembalikan ke format awal (huruf pertama kapital)
            status[0] = toupper(status[0]);
            for (size_t i = 1; i < status.length(); i++) {
                status[i] = tolower(status[i]);
            }
        } else {
            cout << "ERROR: Status harus 'Lunas' atau 'Belum'!" << endl;
            cout << "Silakan coba lagi.\n";
        }
    }
}

// =============================================
// FUNGSI UNTUK MENDAPATKAN TANGGAL SEKARANG
// =============================================
string getCurrentDate() {
    // Mengembalikan tanggal dalam format dd/mm/yyyy
    return "01/01/2023"; // Ganti dengan logika tanggal yang sesuai jika diperlukan
}

// =============================================
// FUNGSI BARU UNTUK MENCATAT TRANSAKSI
// =============================================
void catatTransaksi(string nama, int kamar, int jumlah, string metode, string status) {
    if (jumlahTransaksi < MAX_TRANSAKSI) {
        Transaksi transaksiBaru;
        transaksiBaru.tanggal = getCurrentDate();
        transaksiBaru.namaPenyewa = nama;
        transaksiBaru.kamar = kamar;
        transaksiBaru.jumlah = jumlah;
        transaksiBaru.metode = metode;
        transaksiBaru.status = status;
        
        riwayatTransaksi[jumlahTransaksi++] = transaksiBaru;
    } else {
        cout << "ERROR: Riwayat transaksi penuh!" << endl;
    }
}

// =============================================
// FUNGSI BARU UNTUK MENYIMPAN RIWAYAT TRANSAKSI KE FILE
// =============================================
void simpanRiwayatTransaksi() {
    ofstream file("riwayat_transaksi.txt");
    
    if (!file.is_open()) {
        cout << "ERROR: Tidak bisa membuka file untuk menyimpan riwayat transaksi!" << endl;
        return;
    }
    
    file << "RIWAYAT TRANSAKSI KOS IDAMAN\n";
    file << "Tanggal,Nama Penyewa,Kamar,Jumlah,Metode,Status\n";
    
    for (int i = 0; i < jumlahTransaksi; i++) {
        file << riwayatTransaksi[i].tanggal << ","
             << riwayatTransaksi[i].namaPenyewa << ","
             << riwayatTransaksi[i].kamar << ","
             << riwayatTransaksi[i].jumlah << ","
             << riwayatTransaksi[i].metode << ","
             << riwayatTransaksi[i].status << "\n";
    }
    
    file.close();
}

// =============================================
// MODIFIKASI FUNGSI PEMBAYARAN (CASE 4)
// =============================================
void prosesPembayaran(string nama[], int kamar[], string bayar[], int hargaKamar[], 
                     int durasi[], int indexPenyewa) {
    int totalBayar = hargaKamar[kamar[indexPenyewa]] * durasi[indexPenyewa];
    int finalBayar = totalBayar; // Diskon diabaikan untuk kesederhanaan
    
    cout << "\n========== DETAIL TAGIHAN PEMBAYARAN ==========" << endl;
    cout << "Nama Penyewa     : " << nama[indexPenyewa] << endl;
    cout << "Nomor Kamar      : " << kamar[indexPenyewa] << endl;
    cout << "Total Tagihan    : Rp " << finalBayar << endl;
    
    cout << "\nPilih metode pembayaran:\n";
    cout << "1. Tunai\n2. Transfer Bank\n3. E-Wallet\nPilihan: ";
    int metode;
    cin >> metode;
    
    string metodePembayaran;
    switch (metode) {
        case 1: metodePembayaran = "Tunai"; break;
        case 2: metodePembayaran = "Transfer Bank"; break;
        case 3: metodePembayaran = "E-Wallet"; break;
        default: metodePembayaran = "Lainnya"; break;
    }
    
    // Validasi input status pembayaran
    string status;
    validasiInputStatus(status);
    bayar[indexPenyewa] = status;
    
    // Catat transaksi
    catatTransaksi(nama[indexPenyewa], kamar[indexPenyewa], finalBayar, metodePembayaran, status);
    
    cout << "\n========== TRANSAKSI BERHASIL DICATAT ==========" << endl;
    cout << "Tanggal       : " << getCurrentDate() << endl;
    cout << "Nama Penyewa  : " << nama[indexPenyewa] << endl;
    cout << "Nomor Kamar   : " << kamar[indexPenyewa] << endl;
    cout << "Jumlah        : Rp " << finalBayar << endl;
    cout << "Metode        : " << metodePembayaran << endl;
    cout << "Status        : " << status << endl;
}

// =============================================
// MODIFIKASI FUNGSI MAIN (BAGIAN YANG BERUBAH)
// =============================================


void header() {
    cout << "=============================================" << endl;
    cout << "         SISTEM PENGELOLAAN KOS" << endl;
    cout << "           3 TINGKAT KUALITAS" << endl;
    cout << "    REGULER | VIP | PREMIUM FACILITIES" << endl;
    cout << "=============================================" << endl;
}

void headerSimple() {
    cout << "=============================================" << endl;
    cout << "         SISTEM PENGELOLAAN KOS" << endl;
    cout << "=============================================" << endl;
}

void garis() {
    cout << "---------------------------------------------" << endl;
}

void garisTebal() {
    cout << "=============================================" << endl;
}

void garisTipis() {
    cout << ".............................................." << endl;
}

void pause() {
    cout << "\n[TEKAN ENTER UNTUK MELANJUTKAN]";
    cin.ignore();
    cin.get();
}

void bersihLayar() {
    system("cls");
}

void animasiLoading() {
    cout << "\nMemproses";
    for (int i = 0; i < 5; i++) {
        cout << ".";
        for (int j = 0; j < 100000000; j++); // Simple delay
    }
    cout << " SELESAI!" << endl;
}

void tampilBanner() {
    cout << "*********************************************" << endl;
    cout << "*                                           *" << endl;
    cout << "*        SELAMAT DATANG DI KOS IDAMAN       *" << endl;
    cout << "*          FASILITAS TERLENGKAP             *" << endl;
    cout << "*                                           *" << endl;
    cout << "*********************************************" << endl;
}

void menu() {
    cout << "\n=========== MENU UTAMA KOS IDAMAN ===========" << endl;
    cout << "| 1. Tambah Penyewa Baru                    |" << endl;
    cout << "| 2. Lihat Status Kamar                     |" << endl;
    cout << "| 3. Lihat Data Penyewa                     |" << endl;
    cout << "| 4. Update Status Bayar                    |" << endl;
    cout << "| 5. Hapus Data Penyewa                     |" << endl;
    cout << "| 6. Info Fasilitas Kamar                   |" << endl;
    cout << "| 7. Laporan Keuangan                       |" << endl;
    cout << "| 8. Cari Data Penyewa                      |" << endl;
    cout << "| 9. Backup Data ke File                    |" << endl;
    cout << "| 0. Keluar Program                         |" << endl;
    cout << "=============================================" << endl;
    cout << "Masukkan pilihan Anda: ";
}

void tampilFasilitasReguler() {
    cout << "\n+==========================================+" << endl;
    cout << "|           FASILITAS KAMAR REGULER        |" << endl;
    cout << "+==========================================+" << endl;
    cout << "| - Kamar ukuran 3x4 meter                |" << endl;
    cout << "| - Tempat tidur single bed                |" << endl;
    cout << "| - Lemari pakaian 2 pintu                |" << endl;
    cout << "| - Meja belajar + kursi                   |" << endl;
    cout << "| - Kamar mandi dalam                      |" << endl;
    cout << "| - Wi-Fi gratis                           |" << endl;
    cout << "| - Listrik + air (include)                |" << endl;
    cout << "+==========================================+" << endl;
    cout << "| HARGA: Rp 500.000/bulan                 |" << endl;
    cout << "+==========================================+" << endl;
}

void tampilFasilitasVIP() {
    cout << "\n+==========================================+" << endl;
    cout << "|             FASILITAS KAMAR VIP          |" << endl;
    cout << "+==========================================+" << endl;
    cout << "| - Kamar ukuran 4x5 meter                 |" << endl;
    cout << "| - Tempat tidur queen size                |" << endl;
    cout << "| - Lemari pakaian 2 pintu + cermin        |" << endl;
    cout << "| - Meja belajar + kursi ergonomis         |" << endl;
    cout << "| - Kamar mandi dalam shower               |" << endl;
    cout << "| - AC 1 PK                                |" << endl;
    cout << "| - Wi-Fi gratis                           |" << endl;
    cout << "| - Listrik + air (include)                |" << endl;
    cout << "| - Laundry gratis 2x/minggu               |" << endl;
    cout << "+==========================================+" << endl;
    cout << "| HARGA: Rp 800.000/bulan                 |" << endl;
    cout << "+==========================================+" << endl;
}

void tampilFasilitasPremium() {
    cout << "\n+==========================================+" << endl;
    cout << "|          FASILITAS KAMAR PREMIUM         |" << endl;
    cout << "+==========================================+" << endl;
    cout << "| - Kamar ukuran 5x6 meter                 |" << endl;
    cout << "| - Tempat tidur king size                 |" << endl;
    cout << "| - Meja kerja premium + kursi ergonomis   |" << endl;
    cout << "| - Kamar mandi dalam + shower water heater|" << endl;
    cout << "| - AC                                     |" << endl;
    cout << "| - Wi-Fi premium                          |" << endl;
    cout << "| - Smart TV 43 inch + Netflix             |" << endl;
    cout << "| - Kulkas mini                            |" << endl;
    cout << "| - Microwave + dispenser                  |" << endl;
    cout << "| - Listrik + air (include)                |" << endl;
    cout << "| - Parkir mobil priority                  |" << endl;
    cout << "| - Laundry gratis unlimited               |" << endl;
    cout << "| - Cleaning service 2x/minggu             |" << endl;
    cout << "+==========================================+" << endl;
    cout << "| HARGA: Rp 1.200.000/bulan               |" << endl;
    cout << "+==========================================+" << endl;
}

void tampilSemuaFasilitas() {
    bersihLayar();
    headerSimple();
    cout << "\n          INFORMASI LENGKAP FASILITAS" << endl;
    garisTebal();
    
    tampilFasilitasReguler();
    cout << "\n";
    tampilFasilitasVIP();
    cout << "\n";
    tampilFasilitasPremium();
    
    cout << "\n+==========================================+" << endl;
    cout << "|            FASILITAS UMUM KOS            |" << endl;
    cout << "+==========================================+" << endl;
    cout << "| - Keamanan 24 jam dengan CCTV           |" << endl;
    cout << "| - Dapur umum lengkap                     |" << endl;
    cout << "| - Ruang tamu ber-AC                      |" << endl;
    cout << "| - Area jemur pakaian                     |" << endl;
    cout << "| - Musholla                               |" << endl;
    cout << "| - Parkiran luas                          |" << endl;
    cout << "| - Gazebo untuk santai                    |" << endl;
    cout << "+==========================================+" << endl;
}

void simpanDataKeFile(string nama[], int kamar[], int durasi[], string bayar[], string telepon[], int totalPenyewa) {
    ofstream file("data_penyewa.txt");
    
    if (!file.is_open()) {
        cout << "ERROR: Tidak bisa membuka file untuk menyimpan!" << endl;
        return;
    }
    
    file << totalPenyewa << endl;
    
    for (int i = 0; i < totalPenyewa; i++) {
        file << nama[i] << endl;
        file << kamar[i] << endl;
        file << durasi[i] << endl;
        file << bayar[i] << endl;
        file << telepon[i] << endl;
    }
    
    file.close();
    cout << "SUCCESS: Data berhasil disimpan ke file 'data_penyewa.txt'" << endl;
}

int muatDataDariFile(string nama[], int kamar[], int durasi[], string bayar[], string telepon[], string statusKamar[]) {
    ifstream file("data_penyewa.txt");
    int totalPenyewa = 0;
    
    if (!file.is_open()) {
        cout << "INFO: File 'data_penyewa.txt' tidak ditemukan. Memulai dengan data kosong." << endl;
        simpanRiwayatTransaksi();
    return 0;
    }
    
    file >> totalPenyewa;
    file.ignore();
    
    for (int i = 0; i < totalPenyewa; i++) {
        getline(file, nama[i]);
        file >> kamar[i];
        file >> durasi[i];
        file >> bayar[i];
        file >> telepon[i];
        file.ignore();
        
        statusKamar[kamar[i]] = "Terisi";
    }
    
    file.close();
    cout << "SUCCESS: Data berhasil dimuat dari file. Total penyewa: " << totalPenyewa << endl;
    return totalPenyewa;
}

void backupData(string nama[], int kamar[], int durasi[], string bayar[], string telepon[], int totalPenyewa, string tipeKamar[], int hargaKamar[]) {
    string namaFile = "backup_data_penyewa_complete.txt";
    ofstream file(namaFile.c_str());
    
    if (!file.is_open()) {
        cout << "ERROR: Tidak bisa membuat file backup!" << endl;
        return;
    }
    
    file << "====================================================================" << endl;
    file << "                    SISTEM PENGELOLAAN KOS IDAMAN" << endl;
    file << "                        LAPORAN DATA LENGKAP" << endl;
    file << "====================================================================" << endl;
    file << "Total Penyewa Terdaftar: " << totalPenyewa << " orang" << endl;
    file << "Kapasitas Maksimal: 15 kamar" << endl;
    file << "====================================================================" << endl;
    file << endl;
    
    if (totalPenyewa == 0) {
        file << "INFORMASI: Tidak ada data penyewa yang terdaftar saat ini." << endl;
        file << "Semua kamar dalam status KOSONG dan siap untuk ditempati." << endl;
        file.close();
        cout << "Backup berhasil dibuat: " << namaFile << endl;
        return;
    }
    
    file << "+----+------------------+-------+--------+-----------+----------+------------------+" << endl;
    file << "| No |      Nama        | Kamar | Durasi |    Tipe   |  Status  |   Total Biaya    |" << endl;
    file << "+----+------------------+-------+--------+-----------+----------+------------------+" << endl;
    
    int totalPendapatan = 0;
    for (int i = 0; i < totalPenyewa; i++) {
        int totalBiaya = hargaKamar[kamar[i]] * durasi[i];
        if (bayar[i] == "Lunas") {
            totalPendapatan += totalBiaya;
        }
        
        file << "| " << setw(2) << (i+1) << " | " 
             << setw(16) << nama[i] << " |   " 
             << setw(2) << kamar[i] << "  |  " 
             << setw(2) << durasi[i] << " bl |  " 
             << setw(8) << tipeKamar[kamar[i]] << " | " 
             << setw(8) << bayar[i] << " | Rp " 
             << setw(12) << totalBiaya << " |" << endl;
    }
    
    file << "+----+------------------+-------+--------+-----------+----------+------------------+" << endl;
    file << "|                                            TOTAL PENDAPATAN: Rp " 
         << setw(12) << totalPendapatan << " |" << endl;
    file << "+----+------------------+-------+--------+-----------+----------+------------------+" << endl;
    file << endl;
    
    file << "====================================================================" << endl;
    file << "                        DETAIL LENGKAP PENYEWA" << endl;
    file << "====================================================================" << endl;
    
    for (int i = 0; i < totalPenyewa; i++) {
        file << endl;
        file << "PENYEWA #" << (i+1) << endl;
        file << "--------------------------------------------------------------------" << endl;
        file << "Nama Lengkap      : " << nama[i] << endl;
        file << "Nomor Telepon     : " << telepon[i] << endl;
        file << "Nomor Kamar       : " << kamar[i] << " (Tipe " << tipeKamar[kamar[i]] << ")" << endl;
        file << "Durasi Sewa       : " << durasi[i] << " bulan" << endl;
        file << "Harga per Bulan   : Rp " << hargaKamar[kamar[i]] << endl;
        file << "Status Pembayaran : " << bayar[i] << endl;
        file << "Total Biaya Sewa  : Rp " << (hargaKamar[kamar[i]] * durasi[i]) << endl;
        
        // Tampilkan fasilitas berdasarkan tipe kamar
        file << "Fasilitas Kamar   : ";
        if (tipeKamar[kamar[i]] == "Reguler") {
            file << "Kamar 3x4m, Single Bed, Lemari 2 pintu, Meja belajar," << endl;
            file << "                    Kamar mandi dalam, Wi-Fi, Listrik+Air" << endl;
        } else if (tipeKamar[kamar[i]] == "VIP") {
            file << "Kamar 4x5m, Queen Bed, Lemari 3 pintu, AC," << endl;
            file << "                    shower, Laundry" << endl;
        } else {
            file << "Kamar 5x6m, King Bed, Walk-in closet, AC," << endl;
            file << "                    water heater, tv, Kulkas mini, dll" << endl;
        }
        
        file << "--------------------------------------------------------------------" << endl;
    }
    
    file << endl;
    file << "====================================================================" << endl;
    file << "                       INFORMASI TARIF & FASILITAS" << endl;
    file << "====================================================================" << endl;
    file << "TIPE REGULER (Kamar 1-5)   : Rp 500.000/bulan" << endl;
    file << "- Kamar 3x4m, Single bed, Lemari 2 pintu, Kamar mandi dalam" << endl;
    file << "- Wi-Fi gratis, Listrik + Air include, Parkir motor" << endl;
    file << endl;
    file << "TIPE VIP (Kamar 6-10)      : Rp 800.000/bulan" << endl;
    file << "- Kamar 4x5m, Queen bed, AC 1PK, TV LED 32 inch, Kulkas mini" << endl;
    file << "- Water heater, Wi-Fi , Laundry 2x/minggu, Parkir mobil" << endl;
    file << endl;
    file << "TIPE PREMIUM (Kamar 11-15) : Rp 1.200.000/bulan" << endl;
    file << "- Kamar 5x6m, King bed, AC , Smart TV 43 inch" << endl;
    file << "- water heatert, Cleaning service" << endl;
    file << "====================================================================" << endl;
    
    file.close();
    cout << "SUCCESS: Backup lengkap berhasil dibuat -> " << namaFile << endl;
}

void tampilStatusKamar(string status[], int harga[], string tipe[]) {
    cout << "\n============ STATUS KAMAR KOS IDAMAN ============" << endl;
    cout << "+--------+-----------+-----------+------------------+" << endl;
    cout << "| Kamar  |   Status  |    Tipe   |      Harga       |" << endl;
    cout << "+--------+-----------+-----------+------------------+" << endl;
    
    for (int i = 1; i <= 15; i++) {
        string statusDisplay = status[i];
        if (status[i] == "Kosong") {
            statusDisplay = "TERSEDIA";
        } else {
            statusDisplay = "TERISI";
        }
        
        cout << "|   " << setw(2) << i << "   |  " << setw(8) << statusDisplay 
             << " |  " << setw(8) << tipe[i] 
             << " | Rp " << setw(11) << harga[i] << " |" << endl;
    }
    cout << "+--------+-----------+-----------+------------------+" << endl;
    
    // Tampilkan ringkasan
    int kosong = 0, terisi = 0;
    for (int i = 1; i <= 15; i++) {
        if (status[i] == "Kosong") kosong++;
        else terisi++;
    }
    
    cout << "\n========== RINGKASAN STATUS ==========" << endl;
    cout << "Total Kamar      : 15 kamar" << endl;
    cout << "Kamar Tersedia   : " << kosong << " kamar" << endl;
    cout << "Kamar Terisi     : " << terisi << " kamar" << endl;
    cout << "Tingkat Hunian   : " << (terisi * 100 / 15) << "%" << endl;
    cout << "======================================" << endl;
}

void tampilDataPenyewa(string nama[], int kamar[], int durasi[], 
                      string bayar[], string tipe[], int harga[], int total) {
    cout << "\n================== DATA PENYEWA KOS IDAMAN ==================" << endl;
    
    if (total == 0) {
        cout << "INFO: Belum ada data penyewa yang terdaftar." << endl;
        cout << "Silakan tambah penyewa baru melalui menu utama." << endl;
        return;
    }
    
    cout << "+----+------------------+-------+--------+-----------+----------+------------------+" << endl;
    cout << "| No |      Nama        | Kamar | Durasi |    Tipe   |  Status  |   Total Biaya    |" << endl;
    cout << "+----+------------------+-------+--------+-----------+----------+------------------+" << endl;
    
    int totalPendapatan = 0;
    for (int i = 0; i < total; i++) {
        int totalBiaya = harga[kamar[i]] * durasi[i];
        if (bayar[i] == "Lunas") {
            totalPendapatan += totalBiaya;
        }
        
        cout << "| " << setw(2) << (i+1) << " | " << setw(16) << nama[i] 
             << " |   " << setw(2) << kamar[i] 
             << "  |  " << setw(2) << durasi[i] << " bl |  " << setw(8) << tipe[kamar[i]]
             << " | " << setw(8) << bayar[i] 
             << " | Rp " << setw(12) << totalBiaya << " |" << endl;
    }
    cout << "+----+------------------+-------+--------+-----------+----------+------------------+" << endl;
    cout << "|                                              TOTAL PENDAPATAN: Rp " 
         << setw(12) << totalPendapatan << " |" << endl;
    cout << "+----+------------------+-------+--------+-----------+----------+------------------+" << endl;
}

void tampilKamarKosong(string status[], int harga[], string tipe[]) {
    cout << "\n========== KAMAR YANG TERSEDIA ==========" << endl;
    garis();
    
    bool adaKosong = false;
    
    for (int i = 1; i <= 15; i++) {
        if (status[i] == "Kosong") {
            cout << "Kamar " << setw(2) << i << " | Tipe " << setw(8) << tipe[i] 
                 << " | Rp " << setw(9) << harga[i] << "/bulan";
            if (tipe[i] == "Reguler") {
                cout << " | Kamar mandi dalam, Wi-Fi";
            } else if (tipe[i] == "VIP") {
                cout << " | AC,";
            } else {
                cout << " | AC, Smart TV, kulkas mini";
            }
            cout << endl;
            
            adaKosong = true;
        }
    }
    
    if (!adaKosong) {
        cout << "MAAF: Semua kamar sudah terisi!" << endl;
        cout << "Silakan cek kembali nanti atau hubungi admin." << endl;
    } else {
        cout << "\nTIP: Pilih kamar sesuai budget dan kebutuhan fasilitas Anda!" << endl;
    }
    garis();
}

void inisialisasiKamar(string status[], int harga[], string tipe[]) {
    for (int i = 1; i <= 15; i++) {
        status[i] = "Kosong";
        
        if (i <= 5) {
            tipe[i] = "Reguler";
            harga[i] = 500000;
        } else if (i <= 10) {
            tipe[i] = "VIP";
            harga[i] = 800000;
        } else {
            tipe[i] = "Premium";
            harga[i] = 1200000;
        }
    }
}

void tampilTipeKamar() {
    cout << "\n========== INFORMASI TIPE KAMAR ==========" << endl;
    cout << "TIPE REGULER (Kamar 1-5)   : Rp 500.000/bulan" << endl;
    cout << "TIPE VIP     (Kamar 6-10)  : Rp 800.000/bulan" << endl;
    cout << "TIPE PREMIUM (Kamar 11-15) : Rp 1.200.000/bulan" << endl;
    cout << "===========================================" << endl;
    cout << "Keterangan: Harga sudah termasuk listrik, air, Wi-Fi" << endl;
    cout << "dan akses fasilitas umum kos." << endl;
}

void tampilStatistik(string status[], string bayar[], int total) {
    int kamarTerisi = 0;
    int sudahLunas = 0;
    int belumLunas = 0;
    int pendapatanBulanIni = 0;
    
    for (int i = 1; i <= 15; i++) {
        if (status[i] == "Terisi") {
            kamarTerisi++;
        }
    }
    
    for (int i = 0; i < total; i++) {
        if (bayar[i] == "Lunas") {
            sudahLunas++;
        } else {
            belumLunas++;
        }
    }
    
    cout << "\n============ STATISTIK KOS IDAMAN ============" << endl;
    cout << "Total Kamar         : 15 kamar" << endl;
    cout << "Kamar Terisi        : " << kamarTerisi << " kamar" << endl;
    cout << "Kamar Kosong        : " << (15 - kamarTerisi) << " kamar" << endl;
    garisTipis();
    cout << "Pembayaran Lunas    : " << sudahLunas << " penyewa" << endl;
    cout << "Pembayaran Tertunda : " << belumLunas << " penyewa" << endl;
    cout << "Kapasitas Penyewa   : " << total << "/15 orang" << endl;
    cout << "==============================================" << endl;
}

void cariDataPenyewa(string nama[], int kamar[], int durasi[], string bayar[], string telepon[], string tipeKamar[], int hargaKamar[], int total) {
    if (total == 0) {
        cout << "INFO: Belum ada data penyewa untuk dicari." << endl;
        return;
    }
    
    cout << "\n========== PENCARIAN DATA PENYEWA ==========" << endl;
    cout << "1. Cari berdasarkan Nama" << endl;
    cout << "2. Cari berdasarkan Nomor Kamar" << endl;
    cout << "3. Cari berdasarkan Status Bayar" << endl;
    cout << "Pilih metode pencarian: ";
    
    int metode;
    cin >> metode;
    
    bool ditemukan = false;
    
    switch (metode) {
        case 1: {
            string cariNama;
            cout << "Masukkan nama yang dicari: ";
            cin >> cariNama;
            
            cout << "\nHasil pencarian nama '" << cariNama << "':" << endl;
            garis();
            
            for (int i = 0; i < total; i++) {
                if (nama[i].find(cariNama) != string::npos) {
                    cout << "DITEMUKAN!" << endl;
                    cout << "Nama           : " << nama[i] << endl;
                    cout << "Kamar          : " << kamar[i] << " (Tipe " << tipeKamar[kamar[i]] << ")" << endl;
                    cout << "Telepon        : " << telepon[i] << endl;
                    cout << "Durasi         : " << durasi[i] << " bulan" << endl;
                    cout << "Status Bayar   : " << bayar[i] << endl;
                    cout << "Total Biaya    : Rp " << (hargaKamar[kamar[i]] * durasi[i]) << endl;
                    garis();
                    ditemukan = true;
                }
            }
            break;
        }
        
        case 2: {
            int cariKamar;
            cout << "Masukkan nomor kamar (1-15): ";
            cin >> cariKamar;
            
            cout << "\nHasil pencarian kamar nomor " << cariKamar << ":" << endl;
            garis();
            
            for (int i = 0; i < total; i++) {
                if (kamar[i] == cariKamar) {
                    cout << "DITEMUKAN!" << endl;
                    cout << "Nama           : " << nama[i] << endl;
                    cout << "Kamar          : " << kamar[i] << " (Tipe " << tipeKamar[kamar[i]] << ")" << endl;
                    cout << "Telepon        : " << telepon[i] << endl;
                    cout << "Durasi         : " << durasi[i] << " bulan" << endl;
                    cout << "Status Bayar   : " << bayar[i] << endl;
                    cout << "Total Biaya    : Rp " << (hargaKamar[kamar[i]] * durasi[i]) << endl;
                    garis();
                    ditemukan = true;
                    break;
                }
            }
            break;
        }
        
        case 3: {
            string statusCari;
            cout << "Masukkan status (Lunas/Belum): ";
            cin >> statusCari;
            
            cout << "\nHasil pencarian status '" << statusCari << "':" << endl;
            garis();
            
            for (int i = 0; i < total; i++) {
                if (bayar[i] == statusCari) {
                    cout << "Nama: " << nama[i] << " | Kamar: " << kamar[i] 
                         << " | Status: " << bayar[i] 
                         << " | Biaya: Rp " << (hargaKamar[kamar[i]] * durasi[i]) << endl;
                    ditemukan = true;
                }
            }
            break;
        }
        
        default: {
            cout << "ERROR: Pilihan tidak valid!" << endl;
            return;
        }
    }
    
    if (!ditemukan) {
        cout << "TIDAK DITEMUKAN: Data yang Anda cari tidak ada dalam sistem." << endl;
    }
}

void laporanKeuangan(string nama[], int kamar[], int durasi[], string bayar[], string tipeKamar[], int hargaKamar[], int total) {
    cout << "\n============ LAPORAN KEUANGAN KOS IDAMAN ============" << endl;
    
    if (total == 0) {
        cout << "INFO: Belum ada data untuk laporan keuangan." << endl;
        return;
    }
    
    int totalPendapatanLunas = 0;
    int totalPendapatanBelum = 0;
    int jumlahLunas = 0;
    int jumlahBelum = 0;
    int pendapatanReguler = 0;
    int pendapatanVIP = 0;
    int pendapatanPremium = 0;
    
    for (int i = 0; i < total; i++) {
        int biayaSewa = hargaKamar[kamar[i]] * durasi[i];
        
        if (bayar[i] == "Lunas") {
            totalPendapatanLunas += biayaSewa;
            jumlahLunas++;
        } else {
            totalPendapatanBelum += biayaSewa;
            jumlahBelum++;
        }
        
        if (tipeKamar[kamar[i]] == "Reguler") {
            if (bayar[i] == "Lunas") pendapatanReguler += biayaSewa;
        } else if (tipeKamar[kamar[i]] == "VIP") {
            if (bayar[i] == "Lunas") pendapatanVIP += biayaSewa;
        } else if (tipeKamar[kamar[i]] == "Premium") {
            if (bayar[i] == "Lunas") pendapatanPremium += biayaSewa;
        }
    }
    
    cout << "+==================================================+" << endl;
    cout << "|                RINGKASAN KEUANGAN               |" << endl;
    cout << "+==================================================+" << endl;
    cout << "| Total Pendapatan Lunas    : Rp " << setw(13) << totalPendapatanLunas << " |" << endl;
    cout << "| Total Pendapatan Tertunda : Rp " << setw(13) << totalPendapatanBelum << " |" << endl;
    cout << "| Total Pendapatan Kotor    : Rp " << setw(13) << (totalPendapatanLunas + totalPendapatanBelum) << " |" << endl;
    cout << "+==================================================+" << endl;
    
    cout << "\n+==================================================+" << endl;
    cout << "|            PENDAPATAN PER KATEGORI              |" << endl;
    cout << "+==================================================+" << endl;
    cout << "| Kamar Reguler (Lunas)     : Rp " << setw(13) << pendapatanReguler << " |" << endl;
    cout << "| Kamar VIP (Lunas)         : Rp " << setw(13) << pendapatanVIP << " |" << endl;
    cout << "| Kamar Premium (Lunas)     : Rp " << setw(13) << pendapatanPremium << " |" << endl;
    cout << "+==================================================+" << endl;
    
    cout << "\n+==================================================+" << endl;
    cout << "|               STATUS PEMBAYARAN                  |" << endl;
    cout << "+==================================================+" << endl;
    cout << "| Pembayaran Lunas          : " << setw(2) << jumlahLunas << " penyewa (" << setw(2) << (jumlahLunas * 100 / total) << "%)     |" << endl;
    cout << "| Pembayaran Tertunda       : " << setw(2) << jumlahBelum << " penyewa (" << setw(2) << (jumlahBelum * 100 / total) << "%)     |" << endl;
    cout << "+==================================================+" << endl;
    
    if (jumlahBelum > 0) {
        cout << "\n========== DAFTAR PEMBAYARAN TERTUNDA ==========" << endl;
        cout << "+----+------------------+-------+-----------+------------------+" << endl;
        cout << "| No |      Nama        | Kamar |    Tipe   |   Total Tagihan  |" << endl;
        cout << "+----+------------------+-------+-----------+------------------+" << endl;
        
        int nomor = 1;
        for (int i = 0; i < total; i++) {
            if (bayar[i] == "Belum") {
                int totalTagihan = hargaKamar[kamar[i]] * durasi[i];
                cout << "| " << setw(2) << nomor << " | " << setw(16) << nama[i]
                     << " |   " << setw(2) << kamar[i] << "  |  " << setw(8) << tipeKamar[kamar[i]]
                     << " | Rp " << setw(12) << totalTagihan << " |" << endl;
                nomor++;
            }
        }
        cout << "+----+------------------+-------+-----------+------------------+" << endl;
    }
}

void tampilDetailPenyewaLengkap(string nama[], int kamar[], int durasi[], string bayar[], string telepon[], string tipeKamar[], int hargaKamar[], int total) {
    if (total == 0) {
        cout << "INFO: Belum ada data penyewa untuk ditampilkan." << endl;
        return;
    }
    
    cout << "\n========== DETAIL LENGKAP SEMUA PENYEWA ==========" << endl;
    
    for (int i = 0; i < total; i++) {
        cout << "\n+================================================+" << endl;
        cout << "|              PENYEWA #" << setw(2) << (i+1) << "                   |" << endl;
        cout << "+================================================+" << endl;
        cout << "| Nama Lengkap    : " << nama[i] <<  endl;
        cout << "| Nomor Telepon   : " << telepon[i] << endl;
        cout << "| Nomor Kamar     : " << kamar[i] << " (Tipe " << setw(8) << tipeKamar[kamar[i]] << ")" << endl;
        cout << "| Durasi Sewa     : " <<  durasi[i] << " bulan                  |" << endl;
        cout << "| Harga per Bulan : Rp " <<  hargaKamar[kamar[i]] << " |" << endl;
        cout << "| Status Bayar    : " <<  bayar[i]<< endl;
        cout << "| Total Biaya     : Rp " << (hargaKamar[kamar[i]] * durasi[i])  << endl;
        
        cout << "+================================================+" << endl;
        cout << "|                  FASILITAS                    |" << endl;
        cout << "+================================================+" << endl;
        
        if (tipeKamar[kamar[i]] == "Reguler") {
            cout << "| - Kamar 3x4 meter                           |" << endl;
            cout << "| - Single bed + lemari 2 pintu               |" << endl;
            cout << "| - Kamar mandi dalam + Wi-Fi gratis           |" << endl;
            cout << "| - Listrik & air sudah termasuk              |" << endl;
        } else if (tipeKamar[kamar[i]] == "VIP") {
            cout << "| - Kamar 4x5 meter + AC                      |" << endl;
            cout << "| - Queen bed + lemari 2 pintu                |" << endl;
            cout << "| - TV LED 32\"                                                |" << endl;
            cout << "| - Laundry gratis 2x/minggu                  |" << endl;
        } else {
            cout << "| - Kamar 5x6 meter + AC                      |" << endl;
            cout << "| - King bed + water heater                   |" << endl;
            cout << "| - Smart TV 43\" + kulkas mini               |" << endl;
            cout << "| - Room service 24 jam + cleaning service    |" << endl;
        }
        
        cout << "+================================================+" << endl;
    }
}

void validasiInputNama(string &nama) {
    bool valid = false;
    while (!valid) {
        cout << "Nama penyewa (min 3 karakter): ";
        getline(cin, nama);
        
        if (nama.length() >= 3) {
            valid = true;
        } else {
            cout << "ERROR: Nama harus minimal 3 karakter!" << endl;
        }
    }
}


void validasiInputTelepon(string &telepon) {
    bool valid = false;
    while (!valid) {
        cout << "Nomor telepon (format: 08xxxxxxxxxx): ";
        cin >> telepon;
        
        if (telepon.length() >= 10 && telepon.length() <= 13 && telepon.substr(0, 2) == "08") {
            valid = true;
        } else {
            cout << "ERROR: Format telepon tidak valid! Gunakan format 08xxxxxxxxxx" << endl;
        }
    }
}

void validasiInputDurasi(int &durasi) {
    bool valid = false;
    while (!valid) {
        cout << "Durasi sewa (1-12 bulan): ";
        cin >> durasi;
        
        if (durasi >= 1 && durasi <= 12) {
            valid = true;
        } else {
            cout << "ERROR: Durasi sewa harus antara 1-12 bulan!" << endl;
        }
    }
}

void tampilPromoDiskon() {
    cout << "\n+============================================+" << endl;
    cout << "|              PROMO SPESIAL!               |" << endl;
    cout << "+============================================+" << endl;
    cout << "| Sewa 6 bulan   -> DISKON 5%               |" << endl;
    cout << "| Sewa 9 bulan   -> DISKON 10%              |" << endl;
    cout << "| Sewa 12 bulan  -> DISKON 15%              |" << endl;
    cout << "+============================================+" << endl;
}

int hitungDiskon(int durasi, int totalBiaya) {
    int diskon = 0;
    if (durasi >= 12) {
        diskon = totalBiaya * 15 / 100;
    } else if (durasi >= 9) {
        diskon = totalBiaya * 10 / 100;
    } else if (durasi >= 6) {
        diskon = totalBiaya * 5 / 100;
    }
    return diskon;
}

void tampilStrukPembayaran(string nama, int kamar, string tipe, int harga, int durasi, int totalBiaya, int diskon, string status) {
    cout << "\n+============================================+" << endl;
    cout << "|            STRUK PEMBAYARAN               |" << endl;
    cout << "+============================================+" << endl;
    cout << "| Nama Penyewa  : " <<  nama << endl;
    cout << "| Kamar         : " << kamar << " (Tipe " << tipe << ") " << endl;
    cout << "| Durasi        : " <<  durasi << " bulan " << endl;
    cout << "| Harga/bulan   : Rp " <<  harga  << endl;
    cout << "+============================================+" << endl;
    cout << "| Subtotal      : Rp " <<  totalBiaya << endl;
    cout << "| Diskon        : Rp " <<  diskon<< endl;
    cout << "+============================================+" << endl;
    cout << "| TOTAL BAYAR   : Rp " <<  (totalBiaya - diskon) << endl;
    cout << "| Status        : " << status << endl;
    cout << "+============================================+" << endl;
    cout << "|        TERIMA KASIH & SELAMAT TINGGAL     |" << endl;
    cout << "+============================================+" << endl;
}

int main() {
    string nama[25];
    int kamar[25];
    int durasi[25];
    string bayar[25];
    string telepon[25];
    
    string statusKamar[16];
    int hargaKamar[16];
    string tipeKamar[16];
    
    inisialisasiKamar(statusKamar, hargaKamar, tipeKamar);
    
    int totalPenyewa = muatDataDariFile(nama, kamar, durasi, bayar, telepon, statusKamar);
    int pilihan;
    
    bersihLayar();
    tampilBanner();
    
    cout << "\nSelamat datang di Sistem Pengelolaan Kos Idaman!" << endl;
    cout << "Sistem ini mengelola 15 kamar dengan 3 tipe kualitas premium." << endl;
    cout << "Nikmati fasilitas terlengkap dengan harga terjangkau!" << endl;
    
    tampilTipeKamar();
    pause();
    
    do {
        bersihLayar();
        header();
        tampilStatistik(statusKamar, bayar, totalPenyewa);
        menu();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: {
                bersihLayar();
                header();
                cout << "\n========== PENDAFTARAN PENYEWA BARU ==========" << endl;
                
                if (totalPenyewa >= 25) {
                    cout << "MAAF: Kapasitas maksimal 25 penyewa sudah penuh!" << endl;
                    cout << "Silakan tunggu hingga ada penyewa yang keluar." << endl;
                    pause();
                    break;
                }
                
                tampilKamarKosong(statusKamar, hargaKamar, tipeKamar);
                
                bool adaKosong = false;
                for (int i = 1; i <= 15; i++) {
                    if (statusKamar[i] == "Kosong") {
                        adaKosong = true;
                        break;
                    }
                }
                
                if (!adaKosong) {
                    pause();
                    break;
                }
                
                cout << "\n========== INPUT DATA PENYEWA ==========" << endl;
                cin.ignore();
                
                validasiInputNama(nama[totalPenyewa]);
                validasiInputTelepon(telepon[totalPenyewa]);
                
                do {
                    cout << "Nomor kamar pilihan (1-15): ";
                    cin >> kamar[totalPenyewa];
                    
                    if (kamar[totalPenyewa] < 1 || kamar[totalPenyewa] > 15) {
                        cout << "ERROR: Nomor kamar harus antara 1-15!" << endl;
                        continue;
                    }
                    
                    if (statusKamar[kamar[totalPenyewa]] == "Terisi") {
                        cout << "ERROR: Kamar sudah terisi! Pilih kamar lain." << endl;
                        continue;
                    }
                    
                    cout << "INFO: Anda memilih Kamar " << kamar[totalPenyewa] 
                         << " - Tipe " << tipeKamar[kamar[totalPenyewa]]
                         << " - Rp " << hargaKamar[kamar[totalPenyewa]] << "/bulan" << endl;
                    
                    break;
                } while (true);
                
                if (tipeKamar[kamar[totalPenyewa]] == "Reguler") {
                    tampilFasilitasReguler();
                } else if (tipeKamar[kamar[totalPenyewa]] == "VIP") {
                    tampilFasilitasVIP();
                } else {
                    tampilFasilitasPremium();
                }
                
                tampilPromoDiskon();
                validasiInputDurasi(durasi[totalPenyewa]);
                
                cout << "Status pembayaran (Lunas/Belum): ";
                cin >> bayar[totalPenyewa];
                
                int totalBiaya = hargaKamar[kamar[totalPenyewa]] * durasi[totalPenyewa];
                int diskon = hitungDiskon(durasi[totalPenyewa], totalBiaya);
                
                statusKamar[kamar[totalPenyewa]] = "Terisi";
                totalPenyewa++;
                
                simpanDataKeFile(nama, kamar, durasi, bayar, telepon, totalPenyewa);
                animasiLoading();
                
                cout << "\n========== PENDAFTARAN BERHASIL! ==========" << endl;
                tampilStrukPembayaran(nama[totalPenyewa-1], kamar[totalPenyewa-1], 
                                    tipeKamar[kamar[totalPenyewa-1]], hargaKamar[kamar[totalPenyewa-1]], 
                                    durasi[totalPenyewa-1], totalBiaya, diskon, bayar[totalPenyewa-1]);
                
                pause();
                break;
            }
            
            case 2: {
                bersihLayar();
                header();
                tampilStatusKamar(statusKamar, hargaKamar, tipeKamar);
                pause();
                break;
            }
            
            case 3: {
                bersihLayar();
                header();
                tampilDataPenyewa(nama, kamar, durasi, bayar, tipeKamar, hargaKamar, totalPenyewa);
                
                if (totalPenyewa > 0) {
                    cout << "\nIngin melihat detail lengkap? (y/n): ";
                    char pilihDetail;
                    cin >> pilihDetail;
                    
                    if (pilihDetail == 'y' || pilihDetail == 'Y') {
                        tampilDetailPenyewaLengkap(nama, kamar, durasi, bayar, telepon, tipeKamar, hargaKamar, totalPenyewa);
                    }
                }
                
                pause();
                break;
            }
            
            case 4: {
    bersihLayar();
    header();
    cout << "\n========== SISTEM PEMBAYARAN KOS IDAMAN ==========" << endl;
    
    if (totalPenyewa == 0) {
        cout << "INFO: Belum ada data penyewa untuk diproses pembayaran." << endl;
        pause();
        break;
    }
    
    cout << "\n========== DAFTAR TAGIHAN YANG BELUM LUNAS ==========" << endl;
    garis();
    
    bool adaTagihan = false;
    int nomorUrut = 1;
    
    for (int i = 0; i < totalPenyewa; i++) {
        if (bayar[i] == "Belum") {
            int totalTagihan = hargaKamar[kamar[i]] * durasi[i];
            int diskon = hitungDiskon(durasi[i], totalTagihan);
            int finalTagihan = totalTagihan - diskon;
            
            cout << nomorUrut << ". " << nama[i] << " (Kamar " << kamar[i] 
                 << " - " << tipeKamar[kamar[i]] << ")" << endl;
            cout << "   Tagihan: Rp " << totalTagihan;
            if (diskon > 0) {
                cout << " - Diskon: Rp " << diskon << " = Rp " << finalTagihan;
            }
            cout << " | Durasi: " << durasi[i] << " bulan" << endl;
            cout << "   Telepon: " << telepon[i] << endl;
            garisTipis();
            
            adaTagihan = true;
            nomorUrut++;
        }
    }
    
    if (!adaTagihan) {
        cout << "INFORMASI: Semua penyewa sudah melunasi pembayaran!" << endl;
        cout << "Tidak ada tagihan yang tertunggak saat ini." << endl;
        pause();
        break;
    }
    
    cout << "\n========== SEMUA DATA PENYEWA & STATUS BAYAR ==========" << endl;
    cout << "+----+------------------+-------+----------+------------------+" << endl;
    cout << "| No |      Nama        | Kamar |  Status  |   Total Tagihan  |" << endl;
    cout << "+----+------------------+-------+----------+------------------+" << endl;
    
    for (int i = 0; i < totalPenyewa; i++) {
        int totalTagihan = hargaKamar[kamar[i]] * durasi[i];
        int diskon = hitungDiskon(durasi[i], totalTagihan);
        int finalTagihan = totalTagihan - diskon;
        
        cout << "| " << setw(2) << (i+1) << " | " << setw(16) << nama[i] 
             << " |   " << setw(2) << kamar[i] << "  | " << setw(8) << bayar[i] 
             << " | Rp " << setw(12) << finalTagihan << " |" << endl;
    }
    cout << "+----+------------------+-------+----------+------------------+" << endl;
    
    int nomorPenyewa;
    cout << "\nPilih nomor penyewa untuk proses pembayaran (1-" << totalPenyewa << "): ";
    cin >> nomorPenyewa;
    
    if (nomorPenyewa < 1 || nomorPenyewa > totalPenyewa) {
        cout << "ERROR: Nomor penyewa tidak valid!" << endl;
        pause();
        break;
    }
    
    int indexPenyewa = nomorPenyewa - 1;
    
    if (bayar[indexPenyewa] == "Lunas") {
        cout << "\n========== INFORMASI PEMBAYARAN ==========" << endl;
        cout << "INFO: Penyewa " << nama[indexPenyewa] << " sudah melunasi pembayaran." << endl;
        cout << "Status: LUNAS ?" << endl;
        cout << "Tidak ada tagihan yang perlu dibayar." << endl;
        
        char lihatDetail;
        cout << "\nIngin melihat detail pembayaran? (y/n): ";
        cin >> lihatDetail;
        
        if (lihatDetail == 'y' || lihatDetail == 'Y') {
            int totalBayar = hargaKamar[kamar[indexPenyewa]] * durasi[indexPenyewa];
            int diskon = hitungDiskon(durasi[indexPenyewa], totalBayar);
            
            tampilStrukPembayaran(nama[indexPenyewa], kamar[indexPenyewa], 
                                tipeKamar[kamar[indexPenyewa]], hargaKamar[kamar[indexPenyewa]], 
                                durasi[indexPenyewa], totalBayar, diskon, "LUNAS");
        }
        
        pause();
        break;
    }
    
    int totalBayar = hargaKamar[kamar[indexPenyewa]] * durasi[indexPenyewa];
    int diskon = hitungDiskon(durasi[indexPenyewa], totalBayar);
    int finalBayar = totalBayar - diskon;
    
    cout << "\n========== DETAIL TAGIHAN PEMBAYARAN ==========" << endl;
    cout << "Nama Penyewa     : " << nama[indexPenyewa] << endl;
    cout << "Nomor Kamar      : " << kamar[indexPenyewa] << " (Tipe " << tipeKamar[kamar[indexPenyewa]] << ")" << endl;
    cout << "Nomor Telepon    : " << telepon[indexPenyewa] << endl;
    cout << "Durasi Sewa      : " << durasi[indexPenyewa] << " bulan" << endl;
    cout << "Harga per Bulan  : Rp " << hargaKamar[kamar[indexPenyewa]] << endl;
    garis();
    cout << "Subtotal         : Rp " << totalBayar << endl;
    
    if (diskon > 0) {
        cout << "Diskon Durasi    : Rp " << diskon;
        if (durasi[indexPenyewa] >= 12) {
            cout << " (15% - Sewa 12 bulan)";
        } else if (durasi[indexPenyewa] >= 9) {
            cout << " (10% - Sewa 9 bulan)";
        } else if (durasi[indexPenyewa] >= 6) {
            cout << " (5% - Sewa 6 bulan)";
        }
        cout << endl;
        garis();
    }
    
    cout << "TOTAL YANG HARUS DIBAYAR: Rp " << finalBayar << endl;
    garisTebal();
    
    cout << "\n========== KONFIRMASI PEMBAYARAN ==========" << endl;
    cout << "Apakah pembayaran sebesar Rp " << finalBayar << " sudah diterima?" << endl;
    cout << "1. Ya, pembayaran sudah diterima (LUNAS)" << endl;
    cout << "2. Belum, tunda pembayaran" << endl;
    cout << "3. Batal proses pembayaran" << endl;
    cout << "Pilihan Anda: ";
    
    int pilihanBayar;
    cin >> pilihanBayar;
    
    switch (pilihanBayar) {
        case 1: {
            // Proses pembayaran berhasil
            bayar[indexPenyewa] = "Lunas";
            simpanDataKeFile(nama, kamar, durasi, bayar, telepon, totalPenyewa);
            
            animasiLoading();
            cout << "\n========== PEMBAYARAN BERHASIL! ==========" << endl;
            cout << "SUCCESS: Pembayaran " << nama[indexPenyewa] << " berhasil diproses!" << endl;
            cout << "Status pembayaran telah diubah menjadi LUNAS." << endl;
            cout << "Data telah disimpan ke sistem." << endl;
            
            // Tampilkan struk pembayaran
            tampilStrukPembayaran(nama[indexPenyewa], kamar[indexPenyewa], 
                                tipeKamar[kamar[indexPenyewa]], hargaKamar[kamar[indexPenyewa]], 
                                durasi[indexPenyewa], totalBayar, diskon, "LUNAS");
            
            cout << "\nPEMBYAYARAN TELAH DIKONFIRMASI DAN DICATAT DALAM SISTEM!" << endl;
            break;
        }
        
        case 2: {
            cout << "\n========== PEMBAYARAN DITUNDA ==========" << endl;
            cout << "INFO: Pembayaran " << nama[indexPenyewa] << " belum diproses." << endl;
            cout << "Status tetap: BELUM LUNAS" << endl;
            cout << "Silakan proses pembayaran di lain waktu." << endl;
            cout << "\nCATATAN: Tagihan sebesar Rp " << finalBayar << " masih berlaku." << endl;
            break;
        }
        
        case 3: {
            cout << "\n========== PROSES DIBATALKAN ==========" << endl;
            cout << "INFO: Proses pembayaran dibatalkan." << endl;
            cout << "Tidak ada perubahan pada data penyewa." << endl;
            break;
        }
        
        case 4: {
		    bersihLayar();
		    header();
		    if (totalPenyewa == 0) {
	        cout << "INFO: Belum ada data penyewa untuk diproses pembayaran.\n";
    	    pause();
        	break;
    		}
    
    		// Tampilkan daftar penyewa
		    tampilDataPenyewa(nama, kamar, durasi, bayar, tipeKamar, hargaKamar, totalPenyewa);
    
		    int nomorPenyewa;
		    cout << "\nPilih nomor penyewa untuk proses pembayaran (1-" << totalPenyewa << "): ";
		    cin >> nomorPenyewa;
    
		    if (nomorPenyewa < 1 || nomorPenyewa > totalPenyewa) {
	        cout << "ERROR: Nomor penyewa tidak valid!\n";
	        pause();
	        break;
		    }
    
    int index = nomorPenyewa - 1;
    prosesPembayaran(nama, kamar, bayar, hargaKamar, durasi, index);
    simpanDataKeFile(nama, kamar, durasi, bayar, telepon, totalPenyewa);
    pause();
    break;
}

        default: {
            cout << "ERROR: Pilihan tidak valid! Proses pembayaran dibatalkan." << endl;
            break;
        }
    }
    
    pause();
    break;
}
            
            case 5: {
                bersihLayar();
                header();
                cout << "\n========== HAPUS DATA PENYEWA ==========" << endl;
                
                if (totalPenyewa == 0) {
                    cout << "INFO: Belum ada data penyewa untuk dihapus." << endl;
                    pause();
                    break;
                }
                
                tampilDataPenyewa(nama, kamar, durasi, bayar, tipeKamar, hargaKamar, totalPenyewa);
                
                int nomorHapus;
                cout << "\nPilih nomor penyewa yang akan dihapus: ";
                cin >> nomorHapus;
                
                if (nomorHapus >= 1 && nomorHapus <= totalPenyewa) {
                    cout << "\n========== KONFIRMASI PENGHAPUSAN ==========" << endl;
                    cout << "Nama Penyewa   : " << nama[nomorHapus-1] << endl;
                    cout << "Nomor Kamar    : " << kamar[nomorHapus-1] << endl;
                    cout << "Tipe Kamar     : " << tipeKamar[kamar[nomorHapus-1]] << endl;
                    cout << "Status Bayar   : " << bayar[nomorHapus-1] << endl;
                    cout << "\nAPAKAH ANDA YAKIN INGIN MENGHAPUS DATA INI? (y/n): ";
                    
                    char konfirmasi;
                    cin >> konfirmasi;
                    
                    if (konfirmasi == 'y' || konfirmasi == 'Y') {
                        statusKamar[kamar[nomorHapus-1]] = "Kosong";
                        
                        for (int i = nomorHapus-1; i < totalPenyewa-1; i++) {
                            nama[i] = nama[i+1];
                            kamar[i] = kamar[i+1];
                            durasi[i] = durasi[i+1];
                            bayar[i] = bayar[i+1];
                            telepon[i] = telepon[i+1];
                        }
                        
                        totalPenyewa--;
                        simpanDataKeFile(nama, kamar, durasi, bayar, telepon, totalPenyewa);
                        animasiLoading();
                        
                        cout << "\nSUCCESS: Data penyewa berhasil dihapus!" << endl;
                        cout << "Kamar " << kamar[nomorHapus-1] << " sekarang tersedia untuk penyewa baru." << endl;
                    } else {
                        cout << "Penghapusan dibatalkan." << endl;
                    }
                } else {
                    cout << "ERROR: Nomor penyewa tidak valid!" << endl;
                }
                
                pause();
                break;
            }
            
            case 6: {
                bersihLayar();
                header();
                tampilSemuaFasilitas();
                pause();
                break;
            }
            
            case 7: {
                bersihLayar();
                header();
                laporanKeuangan(nama, kamar, durasi, bayar, tipeKamar, hargaKamar, totalPenyewa);
                pause();
                break;
            }
            
            case 8: {
                bersihLayar();
                header();
                cariDataPenyewa(nama, kamar, durasi, bayar, telepon, tipeKamar, hargaKamar, totalPenyewa);
                pause();
                break;
            }
            
            case 9: {
                bersihLayar();
                header();
                cout << "\n========== BACKUP DATA SISTEM ==========" << endl;
                
                if (totalPenyewa == 0) {
                    cout << "INFO: Tidak ada data untuk di-backup." << endl;
                    cout << "File backup kosong akan tetap dibuat untuk referensi." << endl;
                }
                
                animasiLoading();
                backupData(nama, kamar, durasi, bayar, telepon, totalPenyewa, tipeKamar, hargaKamar);
                
                cout << "\nBackup telah selesai dan siap untuk digunakan!" << endl;
                pause();
                break;
            }
            
            case 0: {
                bersihLayar();
                tampilBanner();
                cout << "\n========== TERIMA KASIH ==========" << endl;
                cout << "Program Sistem Pengelolaan Kos Idaman telah selesai." << endl;
                cout << "Data tersimpan otomatis di file 'data_penyewa.txt'" << endl;
                cout << "Backup lengkap tersedia di 'backup_data_penyewa_complete.txt'" << endl;
                cout << "\nSampai jumpa kembali di Kos Idaman!" << endl;
                cout << "Terima kasih telah menggunakan sistem kami." << endl;
                garisTebal();
                break;
            }
            
            default: {
                cout << "\nERROR: Pilihan tidak valid!" << endl;
                cout << "Silakan pilih menu 0-9 saja." << endl;
                cout << "Perhatikan angka yang Anda masukkan." << endl;
                pause();
                break;
            }
        }
        
    } while (pilihan != 0);
    
    simpanRiwayatTransaksi();
    return 0;
}
