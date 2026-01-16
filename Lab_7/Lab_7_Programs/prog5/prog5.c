// Ebeyn prosesten çocuk prosese veri gönderme
// Sending data from parent process to child process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char write_msg[] = "Message from parent";
    char read_msg[100];
    
    // Pipe oluştur / Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }
    
    // Çocuk proses oluştur / Create child process
    pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    
    if (pid > 0) {  // Ebeyn proses / Parent process
        close(pipefd[0]);  // Okuma ucunu kapat / Close read end
        
        printf("Parent [PID: %d]: Sending message...\n", getpid());
       
        
        write(pipefd[1], write_msg, strlen(write_msg) + 1);
        close(pipefd[1]);  // Yazma ucunu kapat / Close write end
        
        wait(NULL);  // Çocuk prosesi bekle / Wait for child process
        
    } else {  // Çocuk proses / Child process
        close(pipefd[1]);  // Yazma ucunu kapat / Close write end
        
        read(pipefd[0], read_msg, sizeof(read_msg));
        
        printf("Child [PID: %d]: Received message: %s\n", getpid(), read_msg);
     
        
        close(pipefd[0]);  // Okuma ucunu kapat / Close read end
    }
    
    return 0;
}