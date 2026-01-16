// İki pipe kullanarak çift yönlü iletişim
// Bidirectional communication using two pipes

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe1[2];  // Ebeyn -> Çocuk / Parent -> Child
    int pipe2[2];  // Çocuk -> Ebeyn / Child -> Parent
    pid_t pid;
    char parent_msg[] = "Hello from parent";
    char child_msg[] = "Hello from child";
    char buffer[100];
    
    // İki pipe oluştur / Create two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe failed");
        exit(1);
    }
    
    pid = fork();
    
    if (pid > 0) {  // Ebeyn proses / Parent process
        close(pipe1[0]);  // pipe1 okuma ucunu kapat / Close pipe1 read end
        close(pipe2[1]);  // pipe2 yazma ucunu kapat / Close pipe2 write end
        
        // Çocuğa mesaj gönder / Send message to child
        write(pipe1[1], parent_msg, strlen(parent_msg) + 1);
        printf("Parent: Message sent: %s\n", parent_msg);
    
        
        // Çocuktan mesaj al / Receive message from child
        read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent: Message received: %s\n", buffer);
     
        
        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
        
    } else {  // Çocuk proses / Child process
        close(pipe1[1]);  // pipe1 yazma ucunu kapat / Close pipe1 write end
        close(pipe2[0]);  // pipe2 okuma ucunu kapat / Close pipe2 read end
        
        // Ebeynden mesaj al / Receive message from parent
        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child: Message received: %s\n", buffer);
    
        
        // Ebeyne mesaj gönder / Send message to parent
        write(pipe2[1], child_msg, strlen(child_msg) + 1);
        printf("Child: Message sent: %s\n", child_msg);
       
        
        close(pipe1[0]);
        close(pipe2[1]);
    }
    
    return 0;
}