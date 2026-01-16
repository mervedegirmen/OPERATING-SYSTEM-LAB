#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char **envp) {
    // Array to hold new arguments for the child program
    // Alt program için yeni argümanları tutacak dizi
    char *newargv[2];
    int i;
    
    // Set up the argument array
    // Argüman dizisini hazırla
    newargv[0] = "Hello";
    newargv[1] = NULL;  // Must be NULL-terminated / NULL ile sonlandırılmalı
    
    // Print parent process information
    // Ana süreç bilgilerini yazdır
    printf("Parent program: PID: %d  PPID: %d\n", getpid(), getppid());
    // Ana program: PID: %d  PPID: %d
    
    printf("Parent program: Calling exec\n");
    // Ana program: Exec çağrılıyor
    
    // Execute the child program with new arguments and environment
    // Alt programı yeni argümanlar ve environment ile çalıştır
    i = execve("./child", newargv, envp);
    
    // This line only executes if execve fails
    // Bu satır sadece execve başarısız olursa çalışır
    perror("exec2: execve failed\n");
    // exec2: execve başarısız oldu
    
    printf("Parent program: Did we return?\n");
    // Ana program: Dönüş oldu mu?
    
    return 0;
}