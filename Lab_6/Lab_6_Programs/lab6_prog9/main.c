#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid, wait_result;
    
    printf("Parent: PID = %d\n", getpid());
    // Ebeveyn: PID = %d
    
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        // Alt süreç
        printf("Child: PID = %d, Parent PID = %d\n", getpid(), getppid());
        // Çocuk: PID = %d, Ebeveyn PID = %d
        
        printf("Child: Working for 2 seconds...\n");
        // Çocuk: 2 saniye çalışıyor...
        
        sleep(2);
        
        printf("Child: Exiting\n");
        // Çocuk: Çıkış yapılıyor
        
        exit(0);
    }
    else {
        // Parent process
        // Ana süreç
        printf("Parent: Child PID = %d\n", pid);
        // Ebeveyn: Çocuk PID = %d
        
        printf("Parent: Waiting for child...\n");
        // Ebeveyn: Çocuk bekleniyor...
        
        // Wait for any child process
        // Herhangi bir alt süreci bekle
        wait_result = wait(NULL);
        
        printf("Parent: Child with PID %d has finished\n", wait_result);
        // Ebeveyn: PID %d olan çocuk tamamlandı
        
        printf("Parent: Exiting\n");
        // Ebeveyn: Çıkış yapılıyor
    }
    
    return 0;
}