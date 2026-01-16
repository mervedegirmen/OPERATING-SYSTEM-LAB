#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Print child process information
    // Alt süreç bilgilerini yazdır
    printf("Child program: PID: %d  PPID: %d\n", getpid(), getppid());
    // Alt program: PID: %d  PPID: %d
    
    // Print the main message with the first argument
    // İlk argüman ile ana mesajı yazdır
    printf("Main program message: %s\n", argv[0]);
    // Ana program mesajı: %s
    
    return 0;
}