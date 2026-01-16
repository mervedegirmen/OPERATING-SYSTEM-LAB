//prog3.c — Dosya açma örneği


// tr: temel girdi/çıktı (I/O) fonksiyonları için gerekli
// en: required for basic input/output (I/O) functions
#include <stdio.h>

// tr: errno ve perror için gerekli
// en: required for errno and perror
#include <errno.h>

int main() {
    FILE *dosya;

    // tr: Var olmayan bir dosyayı okuma modunda açmayı deneyelim
    // en: Let's try to open a non-existent file in read mode
    dosya = fopen("bu_dosya_yok.txt", "r");

    if (dosya == NULL) {
        // tr: Dosya açılamadı, bir hata oluştu.
        // en: The file could not be opened; an error occurred.

        // tr: perror, bizim mesajımızı ve ardından sistemin hata açıklamasını basar (errno'ya göre).
        // en: perror prints our message followed by the system’s error description (based on errno).
        perror("HATA: Dosya acilamadi");

        // tr: Programın hata ile sonlandığını belirtir
        // en: Indicates the program exited with an error
        return 1;
    }

    // tr: Buraya gelindiyse dosya başarıyla açılmıştır.
    // en: If we reach here, the file was opened successfully.
    printf("Dosya basariyla acildi.\n");

    // tr: Açılan dosyayı kapatalım.
    // en: Close the opened file.
    fclose(dosya);

    // tr: Başarılı biçimde çık.
    // en: Exit successfully.
    return 0;
}