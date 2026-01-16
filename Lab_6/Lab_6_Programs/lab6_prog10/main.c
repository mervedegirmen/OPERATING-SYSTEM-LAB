#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    
    printf("Parent: Creating child process\n");
    // Ebeveyn: Alt süreç oluşturuluyor
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process - exits with code 42
        // Alt süreç - 42 koduyla çıkış yapıyor
        printf("Child: PID = %d\n", getpid());
        // Çocuk: PID = %d
        
        printf("Child: Exiting with code 42\n");
        // Çocuk: 42 koduyla çıkış yapılıyor
        
        exit(42);
    }
    else {
        // Parent process
        // Ana süreç
        printf("Parent: Waiting for child (PID: %d)\n", pid);
        // Ebeveyn: Çocuk (PID: %d) bekleniyor
        
        // Wait and capture exit status
        // Bekle ve çıkış durumunu yakala
        pid_t result = wait(&status);
        
        printf("\n=== Wait Results ===\n");
        // === Wait Sonuçları ===
        
        printf("Returned PID: %d\n", result);
        // Dönen PID: %d
        
        // Check if child exited normally
        // Çocuk normal şekilde çıktı mı kontrol et
        if (WIFEXITED(status)) {
            printf("Child exited normally\n");
            // Çocuk normal şekilde çıktı
            
            int exit_code = WEXITSTATUS(status);
            printf("Exit code: %d\n", exit_code);
            // Çıkış kodu: %d
        }
        else {
            printf("Child did not exit normally\n");
            // Çocuk normal şekilde çıkmadı
        }
    }
    
    return 0;
}