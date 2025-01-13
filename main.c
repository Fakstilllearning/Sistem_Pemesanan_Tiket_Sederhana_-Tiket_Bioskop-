#include <stdio.h>
#include <string.h>

// Ukuran & jumlah kursi teater
#define ROWS 5
#define COLS 10
#define MAX_SEATS 50
#define MAX_FILMS 6

// Data film
char *judul[] = {"1 Imam 2 Makmum", "Miracle In Cell 2", "Happy Family", "Venom: The Last Dance", "Dirty Angels", "Pengantin Setan"};
float harga[] = {44000, 48000, 43000, 50000, 45000, 47000};
char *jadwal[] = {"13:00", "16:00", "16:30", "17:00", "19:00", "19:30"};

// Array untuk menyimpan status kursi untuk setiap film (0 = kosong, 1 = terisi)
int kursi[MAX_FILMS][ROWS][COLS] = {0};

// Fungsi-fungsi untuk menu utama
void tampilkanMenu() {
    printf("\n=============================== Fancynema App ===============================\n");
    printf("Selamat Datang di Fancynema!\n");
    printf("Pesan Praktis, Nonton Fantastis!\n\n");
    printf("Nikmati pengalaman memesan tiket bioskop yang cepat, mudah, dan tanpa ribet.\n");
    printf("Dengan Fancynema App, Anda hanya butuh beberapa klik untuk mendapatkan tiket\n");
    printf("ke film favorit Anda, kapan saja dan di mana saja. Rasakan kemudahan praktis\n");
    printf("yang menjadikan momen nonton Anda semakin fantastis!\n\n");
    printf("1. Lihat Daftar Film\n");
    printf("2. Pesan Tiket\n");
    printf("3. Keluar\n");
}

// Menu untuk daftar film
void tampilkanFilm() {
    printf("\n=============== DAFTAR FILM ===============\n");
    for(int i = 0; i < MAX_FILMS; i++) {
        printf("\nNama Film  : %s", judul[i]);
        printf("\nHarga      : Rp %.2f", harga[i]);
        printf("\nJadwal     : %s WIB", jadwal[i]);
        
        // Tampilan denah kursi untuk setiap film
        printf("\n\nDenah Kursi Film %s:", judul[i]);
        printf("\n(0 = Kosong, 1 = Terisi)\n\n");
        for(int row = 0; row < ROWS; row++) {
            for(int col = 0; col < COLS; col++) {
                printf("%d ", kursi[i][row][col]);
            }
            printf("\n");
        }
        printf("\n===========================================\n");
    }
}

void tampilkanDenah(int film_idx) {
    printf("\n=== Denah Kursi Film %s ===\n", judul[film_idx]);
    printf("(0 = Kosong, 1 = Terisi)\n\n");
    
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%d ", kursi[film_idx][i][j]);
        }
        printf("\n");
    }
}

// Menu untuk pesan tiket
void pesanTiket() {
    int pilihan_film, jumlah_tiket;
    int nomor_kursi[MAX_SEATS];
    
    // Tampilan film dan pilih film
    printf("\n============= PESAN TIKET =============\n");
    for(int i = 0; i < MAX_FILMS; i++) {
        printf("\n%d. Nama Film : %s", i+1, judul[i]);
        printf("\n   Harga     : Rp %.2f", harga[i]);
        printf("\n   Jadwal    : %s WIB\n", jadwal[i]);
    }
    
    printf("\nPilih film (1-6): ");
    scanf("%d", &pilihan_film);
    
    if(pilihan_film < 1 || pilihan_film > 6) {
        printf("Pilihan film tidak valid!\n");
        return;
    }
    
    // Tampilan denah dan pilih jumlah tiket
    tampilkanDenah(pilihan_film-1);
    printf("\nMasukkan jumlah tiket: ");
    scanf("%d", &jumlah_tiket);
    
    if(jumlah_tiket > MAX_SEATS || jumlah_tiket < 1) {
        printf("Jumlah tiket tidak valid!\n");
        return;
    }
    
    // Pilih kursi
    printf("\nPilih nomor kursi (1-%d): \n", MAX_SEATS);
    for(int i = 0; i < jumlah_tiket; i++) {
        do {
            printf("\nKursi ke-%d: ", i+1);
            scanf("%d", &nomor_kursi[i]);
            
            int baris = (nomor_kursi[i]-1) / COLS;
            int kolom = (nomor_kursi[i]-1) % COLS;
            
            if(nomor_kursi[i] < 1 || nomor_kursi[i] > MAX_SEATS) {
                printf("Nomor kursi tidak valid!\n");
                continue;
            }
            
            if(kursi[pilihan_film-1][baris][kolom] == 1) {
                printf("Kursi sudah terisi!\n");
                continue;
            }
            
            kursi[pilihan_film-1][baris][kolom] = 1;
            break;
        } while(1);
        
        tampilkanDenah(pilihan_film-1);
    }
    
    // Cetak tiket bioskop
    float total = harga[pilihan_film-1] * jumlah_tiket;
    printf("\n========== TIKET BIOSKOP ==========\n");
    printf("Nama Film: %s\n", judul[pilihan_film-1]);
    printf("Jadwal: %s WIB\n", jadwal[pilihan_film-1]);
    printf("Jumlah Tiket: %d\n", jumlah_tiket);
    printf("Nomor Kursi: ");
    
    // Cetak nomor kursi dengan koma
    for(int i = 0; i < jumlah_tiket; i++) {
        printf("%d", nomor_kursi[i]);
        if(i < jumlah_tiket - 1) {
            printf(", ");
        }
    }
    
    printf("\nTotal: Rp %.2f\n", total);
    printf("===================================\n");
}

// Lanjutan untuk fungsi-fungsi menu utama
int main() {
    int pilihan;
    
    do {
        tampilkanMenu();
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                tampilkanFilm();
                break;
            case 2:
                pesanTiket();
                break;
            case 3:
                printf("\nTerima kasih telah menggunakan layanan Fancynema App!\n");
                break;
            default:
                printf("\nPilihan tidak valid!\n");
        }
        
        if(pilihan != 3) {
            printf("\nTekan Enter untuk melanjutkan...");
            getchar();
            getchar();
        }
    } while(pilihan != 3);
    
    return 0;
}