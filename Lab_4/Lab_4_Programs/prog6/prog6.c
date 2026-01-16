// tr: Komut satırı argümanlarıyla çalışan basit bir hesap makinesi.
//     Kullanım: ./prog6_run <islem> <a> <b>
//     islem: add | sub | mul | div
// en: A simple calculator that uses command-line arguments.
//     Usage: ./prog6_run <op> <a> <b>
//     op: add | sub | mul | div

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

static void print_usage(const char *prog) {
    // tr: Kullanım bilgisini yaz
    // en: Print usage info
    printf("Kullanim / Usage:\n");
    printf("  %s <islem/op> <a> <b>\n", prog);
    printf("  islem/op: add | sub | mul | div\n");
    printf("Ornek / Example:\n");
    printf("  %s add 5 7\n", prog);
}

int main(int argc, char *argv[]) {
    // tr: Argüman kontrolü
    // en: Check arguments
    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }

    // tr: İşlem adını ve sayıları alalım.
    // en: Parse operation and numbers.
    const char *op = argv[1];
    int a = atoi(argv[2]); // tr: basit çeviri, hata kontrolü yapmaz
                           // en: simple conversion, no error check
    int b = atoi(argv[3]);

    int result = 0;

    // tr: İşleme göre yönlendir.
    // en: Dispatch by operation.
    if (strcmp(op, "add") == 0) {
        result = add(a, b);
        printf("%d + %d = %d\n", a, b, result);
    } else if (strcmp(op, "sub") == 0) {
        result = sub(a, b);
        printf("%d - %d = %d\n", a, b, result);
    } else if (strcmp(op, "mul") == 0) {
        result = mul(a, b);
        printf("%d * %d = %d\n", a, b, result);
    } else if (strcmp(op, "div") == 0) {
        int ok = divide(a, b, &result);
        if (ok != 0) {
            // tr: Bölme hatası (b = 0)
            // en: Division error (b = 0)
            fprintf(stderr, "HATA / ERROR: bolen/divisor 0 olamaz / cannot be 0\n");
            return 2;
        }
        printf("%d / %d = %d\n", a, b, result);
    } else {
        // tr: Geçersiz işlem / en: Invalid operation
        fprintf(stderr, "HATA / ERROR: Gecersiz islem/op: %s\n", op);
        print_usage(argv[0]);
        return 3;
    }

    return 0;
}