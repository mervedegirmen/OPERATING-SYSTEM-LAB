#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Print child process information
    // Alt süreç bilgilerini yazdır
    printf("Child program: PID: %d  PPID: %d\n", getpid(), getppid());
    
    printf("Child program: Running successfully\n");
    // Alt program: Başarıyla çalışıyor
    
    return 0;
}