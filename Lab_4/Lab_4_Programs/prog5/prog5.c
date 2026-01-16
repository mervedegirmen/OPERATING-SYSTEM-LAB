// tr: Basit toplama yapan örnek (tek dosya).
// en: A simple addition example (single file).

#include <stdio.h>

int main(void) {
    // tr: İki tamsayı tanımlayalım.
    // en: Define two integers.
    int a = 5;
    int b = 6;
    int c = a + b; // tr: Toplama işlemi / en: Addition

    // tr: Sonucu yazdıralım.
    // en: Print the result.
    printf("%d + %d = %d\n", a, b, c);
    return 0;
}