#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int i;
    pid_t pid;
    // Print parent process information
    // Ana süreç bilgilerini yazdır
    printf("Parent program: PID: %d  PPID: %d\n", getpid(), getppid());
    
	pid= fork();
	
	if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        // Alt süreç
        printf("Child: Executing command...\n");
        // Çocuk: Komut çalıştırılıyor...
        
        i = execl("./child", "child_program", NULL);
        
        perror("exec failed");
        exit(1);
    }
    else {
        // Parent process
        // Ana süreç
        printf("Parent running: PID: %d  PPID: %d\n", getpid(), getppid());
       
	}
	
    return 0;
}