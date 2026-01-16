#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    pid_t wait_return;
    
    printf("Parent: PID = %d\n", getpid());
    // Ebeveyn: PID = %d
    
    printf("Parent: Creating child process\n\n");
    // Ebeveyn: Alt süreç oluşturuluyor
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process: execute child_task program
        // Alt süreç: child_task programını çalıştır
        execl("./child_task", "child_task", NULL);
        
        // If exec fails
        // Exec başarısız olursa
        perror("exec failed");
        return 255;
    }
    else {
        // Parent process: wait for child
        // Ana süreç: çocuğu bekle
        printf("Parent: Child PID = %d\n", pid);
        // Ebeveyn: Çocuk PID = %d
        
        printf("Parent: Waiting for child...\n\n");
        // Ebeveyn: Çocuk bekleniyor...
        
        wait_return = wait(&status);
        
        printf("\n=== Wait Results ===\n");
        // === Wait Sonuçları ===
        
        printf("wait() returned PID: %d\n", wait_return);
        // wait() dönen PID: %d
        
        printf("status (raw value): %d\n", status);
        // status (ham değer): %d
        
        printf("Child return value (WEXITSTATUS): %d\n", WEXITSTATUS(status));
        // Çocuk dönüş değeri (WEXITSTATUS): %d
        
        printf("\nParent: Exiting\n");
        // Ebeveyn: Çıkış yapılıyor
    }
    
    return 0;
}