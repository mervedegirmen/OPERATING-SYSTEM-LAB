#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Check if correct number of arguments provided
    // Doğru sayıda argüman verilip verilmediğini kontrol et
    if (argc != 3) {
        printf("Usage: %s <text> <count>\n", argv[0]);
        // Kullanım: %s <metin> <sayı>
        return 1;
    }
    
    char *text = argv[1];
    int count = atoi(argv[2]);
    
    // Print child process information
    // Alt süreç bilgilerini yazdır
    printf("Child program (printc): PID: %d  PPID: %d\n", getpid(), getppid());
    
    printf("Printing '%s' %d times:\n", text, count);
    // '%s' metni %d kez yazdırılıyor:
    printf("-----------------------------------\n");
    
    // Print the text 'count' times
    // Metni 'count' kez yazdır
    for (int i = 1; i <= count; i++) {
        printf("%d: %s\n", i, text);
    }
    
    printf("-----------------------------------\n");
    printf("Child program: Finished\n");
    // Alt program: Tamamlandı
    
    return 0;
}