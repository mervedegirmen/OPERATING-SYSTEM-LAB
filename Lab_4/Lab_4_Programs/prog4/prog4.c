// tr: Bu program, gdb ile hata ayıklamayı göstermek için bilerek iki hata içerir:
//     1) Dizi tasması / sınır aşımı (buffer overflow)
//     2) Sıfıra bölme (division by zero)
// en: This program intentionally contains two bugs to demonstrate debugging with gdb:
//     1) Array out-of-bounds (buffer overflow)
//     2) Division by zero

#include <stdio.h>
#include <string.h>

int div(int a, int b) {
    // tr: HATA NOKTASI #1: b = 0 olduğunda sıfıra bölme hatası oluşur.
    // en: BUG POINT #1: When b = 0, division by zero occurs.
    return a / b;
}

void copy(char *dest, const char *src) {
    // tr: HATA NOKTASI #2: strcpy uzunluk kontrolü yapmaz, kaynak hedefi taşırabilir.
    // en: BUG POINT #2: strcpy does not check lengths; source may overflow dest.
    strcpy(dest, src);
}

int main(int argc, char *argv[]) {
    // tr: Küçük bir tampon bellek ayırıyoruz.
    // en: We allocate a small buffer.
    char buf[8] = {0};

    // tr: Kullanım bilgisi
    // en: Usage info
    if (argc < 3) {
        // tr: argv[1] -> buf'a kopyalanacak metin, argv[2] -> bölmede kullanılacak bölen
        // en: argv[1] -> text to copy into buf, argv[2] -> divisor for division
        printf("Kullanim / Usage:\n");
        printf("  %s <metin/text> <bolen/divisor>\n", argv[0]);
        printf("Ornek / Example:\n");
        printf("  %s merhaba/hello 2\n", argv[0]);
        return 1;
    }

    // tr: 1) Potansiyel taşma: Uzun bir metin verirseniz buf[8]'i taşır.
    // en: 1) Potential overflow: A long text will overflow buf[8].
    copy(buf, argv[1]);

    // tr: 2) Potansiyel sıfıra bölme: argv[2] = 0 verilirse hata.
    // en: 2) Potential division by zero: if argv[2] = 0, it's a bug.
    int divisor = 0;
    sscanf(argv[2], "%d", &divisor);

    // tr: Amaç: gdb ile bu satırlarda durup değişkenleri incelemek.
    // en: Goal: Stop here with gdb and inspect variables.
    int result = div(100, divisor);

    // tr: Çıktıları yaz
    // en: Print outputs
    printf("buf: '%s'\n", buf);
    printf("100 / %d = %d\n",divisor, result);

    return 0;
}