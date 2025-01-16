#include <stdio.h>
#include <string.h>

// Ukuran & jumlah kursi teater
#define ROWS 5
#define COLS 10
#define MAX_SEATS 50
#define MAX_FILMS 4
#define MAX_DAYS 2

// Data film untuk Sabtu
char *judul_sabtu[] = {"1 Imam 2 Makmum", "Miracle In Cell 2", "Happy Family", "Venom: The Last Dance"};
float harga_sabtu[] = {44000, 48000, 43000, 50000};
char *jadwal_sabtu[] = {"13:00", "16:00", "16:30", "17:00"};
int studio_sabtu[] = {1, 2, 3, 4};

// Data film untuk Minggu
char *judul_minggu[] = {"Pengantin Setan", "Dirty Angels", "Avatar 2", "Fast X"};
float harga_minggu[] = {45000, 47000, 55000, 52000};
char *jadwal_minggu[] = {"14:00", "15:30", "18:00", "19:00"};
int studio_minggu[] = {1, 2, 3, 4};

// Array untuk menyimpan status kursi untuk setiap film di setiap hari (0 = kosong, 1 = terisi)
int kursi_sabtu[MAX_FILMS][ROWS][COLS] = {0};
int kursi_minggu[MAX_FILMS][ROWS][COLS] = {0};

// Fungsi untuk menampilkan garis
void tampilkan_garis() {
    printf("===========================================================\n");
}

void tampilkan_kotak(const char* hari) {
    printf("\n ============                           \n| HARI %s |\n ============\n", hari);
}

void tampilkanMenu() {
    tampilkan_garis();
    printf("                       Fancynema App                 \n");
    tampilkan_garis();
    printf("Selamat Datang di Fancynema!\n");
    printf("Pesan Praktis, Nonton Fantastis!\n\n");
    printf("Nikmati pengalaman memesan tiket bioskop yang cepat, mudah,\ndan tanpa ribet. Dengan Fancynema App, Anda hanya butuh\nbeberapa klik untuk mendapatkan tiket ke film favorit Anda,\nkapan saja dan di mana saja.\n\n");
    printf("1. Lihat Daftar Film\n");
    printf("2. Pesan Tiket\n");
    printf("3. Keluar\n");
}

void tampilkanFilmPerHari(char *judul, float *harga, char **jadwal, int *studio, int kursi[][ROWS][COLS], const char hari) {
    tampilkan_kotak(hari);
    for(int i = 0; i < MAX_FILMS; i++) {
        printf("\nNama Film  : %s", judul[i]);
        printf("\nHarga      : Rp %.2f", harga[i]);
        printf("\nJadwal     : %s WIB", jadwal[i]);
        printf("\nStudio     : %d", studio[i]);
        
        printf("\n\nDenah Kursi Film %s:", judul[i]);
        printf("\n(0 = Kosong, 1 = Terisi)\n\n");
        for(int row = 0; row < ROWS; row++) {
            for(int col = 0; col < COLS; col++) {
                printf("%d ", kursi[i][row][col]);
            }
            printf("\n");
        }
        printf("\n===========================================================\n");
    }
}

void tampilkanFilm() {
    tampilkan_garis();
    printf("                       DAFTAR FILM                 \n");
    tampilkan_garis();
    
    // Tampilkan film untuk hari Sabtu
    tampilkanFilmPerHari(judul_sabtu, harga_sabtu, jadwal_sabtu, studio_sabtu, kursi_sabtu, "SABTU");
    
    // Tampilkan film untuk hari Minggu
    tampilkanFilmPerHari(judul_minggu, harga_minggu, jadwal_minggu, studio_minggu, kursi_minggu, "MINGGU");
}

void tampilkanDenah(int film_idx, int hari) {
    char **judul = (hari == 1) ? judul_sabtu : judul_minggu;
    int (*kursi)[ROWS][COLS] = (hari == 1) ? kursi_sabtu : kursi_minggu;
    
    printf("\n=== Denah Kursi Film %s ===\n", judul[film_idx]);
    printf("(0 = Kosong, 1 = Terisi)\n\n");
    
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%d ", kursi[film_idx][i][j]);
        }
        printf("\n");
    }
}

void pesanTiket() {
    int pilihan_hari, pilihan_film, jumlah_tiket;
    int nomor_kursi[MAX_SEATS];
    
    tampilkan_garis();
    printf("                        PESAN TIKET                \n");
    tampilkan_garis();
    
    // Pilih hari
    printf("\nPilih Hari:\n");
    printf("1. Sabtu\n");
    printf("2. Minggu\n");
    printf("Pilihan hari (1-2): ");
    scanf("%d", &pilihan_hari);
    
    if(pilihan_hari < 1 || pilihan_hari > 2) {
        printf("Pilihan hari tidak valid!\n");
        return;
    }
    
    // Tentukan array yang akan digunakan berdasarkan hari
    char **judul = (pilihan_hari == 1) ? judul_sabtu : judul_minggu;
    float *harga = (pilihan_hari == 1) ? harga_sabtu : harga_minggu;
    char **jadwal = (pilihan_hari == 1) ? jadwal_sabtu : jadwal_minggu;
    int *studio = (pilihan_hari == 1) ? studio_sabtu : studio_minggu;
    int (*kursi)[ROWS][COLS] = (pilihan_hari == 1) ? kursi_sabtu : kursi_minggu;
    
    // Tampilkan film untuk hari yang dipilih
    for(int i = 0; i < MAX_FILMS; i++) {
        printf("\n%d. Nama Film : %s", i+1, judul[i]);
        printf("\n   Harga     : Rp %.2f", harga[i]);
        printf("\n   Jadwal    : %s WIB", jadwal[i]);
        printf("\n   Studio    : %d\n", studio[i]);
    }
    
    printf("\nPilih film (1-%d): ", MAX_FILMS);
    scanf("%d", &pilihan_film);
    
    if(pilihan_film < 1 || pilihan_film > MAX_FILMS) {
        printf("Pilihan film tidak valid!\n");
        return;
    }
    
    tampilkanDenah(pilihan_film-1, pilihan_hari);
    printf("\nMasukkan jumlah tiket: ");
    scanf("%d", &jumlah_tiket);
    
    if(jumlah_tiket > MAX_SEATS || jumlah_tiket < 1) {
        printf("Jumlah tiket tidak valid!\n");
        return;
    }
    
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
        
        tampilkanDenah(pilihan_film-1, pilihan_hari);
    }
    
    float total = harga[pilihan_film-1] * jumlah_tiket;
    tampilkan_garis();
    printf("                    TIKET BIOSKOP               \n");
    tampilkan_garis();
    printf("Hari: %s\n", pilihan_hari == 1 ? "Sabtu" : "Minggu");
    printf("Nama Film: %s\n", judul[pilihan_film-1]);
    printf("Jadwal: %s WIB\n", jadwal[pilihan_film-1]);
    printf("Studio: %d\n", studio[pilihan_film-1]);
    printf("Jumlah Tiket: %d\n", jumlah_tiket);
    printf("Nomor Kursi: ");
    
    for(int i = 0; i < jumlah_tiket; i++) {
        printf("%d", nomor_kursi[i]);
        if(i < jumlah_tiket - 1) {
            printf(", ");
        }
    }
    
    printf("\nTotal: Rp %.2f\n", total);
    tampilkan_garis();
}

int main() {
    int pilihan;
    
    do {
        tampilkanMenu();
        printf("Pilihan Anda: "
        );
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
            printf("\nTekan Enter untuk melanjutkan...\n");
            getchar();
            getchar();
        }
    } while(pilihan != 3);
    
    return 0;
}
