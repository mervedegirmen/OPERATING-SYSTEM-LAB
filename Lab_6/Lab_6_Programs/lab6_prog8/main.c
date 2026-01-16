#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    // Array of arguments for execv (must end with NULL)
    // execv için argüman dizisi (NULL ile bitmeli)
    char *args[] = {
        "printc",           // Program name / Program adı
        "Hello World",      // Text to print / Yazdırılacak metin
        "5",                // Number of times / Tekrar sayısı
        NULL                // Must be NULL terminated / NULL ile sonlandırılmalı
    };
    
    // Print parent process information
    // Ana süreç bilgilerini yazdır
    printf("Parent program: PID: %d  PPID: %d\n", getpid(), getppid());
    
    printf("Parent program: Creating child process\n");
    // Ana program: Alt süreç oluşturuluyor
    
    // Create child process
    // Alt süreç oluştur
    pid = fork();
    
    if (pid < 0) {
        // Fork failed
        // Fork başarısız oldu
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process: execute printc program with array of arguments
        // Alt süreç: printc programını argüman dizisi ile çalıştır
        printf("Child process created: PID: %d\n", getpid());
        // Alt süreç oluşturuldu: PID: %d
        
        // Execute printc with arguments array
        // printc'yi argüman dizisi ile çalıştır
        execv("./printc", args);
        
        // If exec fails
        // Exec başarısız olursa
        perror("execv failed");
        return 1;
    }
    else {
        // Parent process: wait for child to complete
        // Ana süreç: alt sürecin tamamlanmasını bekle
        printf("Parent program: Waiting for child (PID: %d)\n", pid);
        // Ana program: Alt süreç (PID: %d) bekleniyor
        
        wait(NULL);
        
        printf("Parent program: Child completed\n");
        // Ana program: Alt süreç tamamlandı
        
        printf("Parent program: Exiting\n");
        // Ana program: Çıkış yapılıyor
    }
    
    return 0;
}