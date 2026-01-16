// Tek bir proses içinde pipe kullanımı
// Using pipe within a single process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];  // Pipe dosya tanımlayıcıları / Pipe file descriptors
    char write_msg[] = "Hello from pipe!";
    char read_msg[100];
    
    // Pipe oluştur / Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }
    
    // Pipe'a yaz / Write to pipe
    write(pipefd[1], write_msg, strlen(write_msg) + 1);
    
    // Pipe'dan oku / Read from pipe
    read(pipefd[0], read_msg, sizeof(read_msg));
    
    printf("Read message: %s\n", read_msg);
   
    
    // Dosya tanımlayıcıları kapat / Close file descriptors
    close(pipefd[0]);
    close(pipefd[1]);
    
    return 0;
}