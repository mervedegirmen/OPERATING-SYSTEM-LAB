// tr: Basit bir hesap makinesi için fonksiyon bildirileri.
// en: Function declarations for a simple calculator.

#ifndef CALCULATOR_H
#define CALCULATOR_H

// tr: Dört temel işlem fonksiyonları
// en: Four basic arithmetic operations
int add(int a, int b);      // tr: Toplama / en: Addition
int sub(int a, int b);      // tr: Çıkarma / en: Subtraction
int mul(int a, int b);      // tr: Çarpma / en: Multiplication

// tr: Bölme için güvenli bir arayüz: bölen 0 ise hata kodu döndürür (örn. -1),
//     sonucu *out parametresine yazar.
// en: Safe division: returns error code (e.g., -1) if divisor is 0,
//     writes the result to *out.
int divide(int a, int b, int *out);

#endif // CALCULATOR_H