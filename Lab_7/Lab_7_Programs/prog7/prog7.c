// Ana program - Çocuk program ile çift yönlü iletişim
// Parent program - Bidirectional communication with child program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe1[2];  // Ebeyn -> Çocuk / Parent -> Child
    int pipe2[2];  // Çocuk -> Ebeyn / Child -> Parent
    pid_t pid;
    char message[100];
    char buffer[100];
    char fd_str1[10], fd_str2[10];
    
    printf("=== Parent Program Started ===\n");
 
    
    // İki pipe oluştur / Create two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe failed");
        exit(1);
    }
    
    printf("Pipe1 (Parent->Child): read=%d, write=%d \n", pipe1[0], pipe1[1]);
    // Pipe1 (Ebeyn->Çocuk): okuma=%d, yazma=%d
    printf("Pipe2 (Child->Parent): read=%d, write=%d \n\n", pipe2[0], pipe2[1]);
    // Pipe2 (Çocuk->Ebeyn): okuma=%d, yazma=%d
    
    pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    
    if (pid == 0) {  // Çocuk proses / Child process
        close(pipe1[1]);  // pipe1 yazma ucunu kapat / Close pipe1 write end
        close(pipe2[0]);  // pipe2 okuma ucunu kapat / Close pipe2 read end
        
        // Dosya tanımlayıcılarını string'e çevir
        // Convert file descriptors to strings
        sprintf(fd_str1, "%d", pipe1[0]);  // Okuma ucu / Read end
        sprintf(fd_str2, "%d", pipe2[1]);  // Yazma ucu / Write end
        
        // Alt programı çalıştır / Execute child program
        execl("./child", "child", fd_str1, fd_str2, NULL);
        
        // execl başarısız olursa / If execl fails
        perror("execl failed");
        exit(1);
        
    } else {  // Ebeyn proses / Parent process
        close(pipe1[0]);  // pipe1 okuma ucunu kapat / Close pipe1 read end
        close(pipe2[1]);  // pipe2 yazma ucunu kapat / Close pipe2 write end
        
        printf("Parent [PID: %d]: Communication starting... \n", getpid());
        // Ebeyn [PID: %d]: Mesajlaşma başlıyor...
        printf(" Type 'exit' to quit. \n\n");
        // Çıkmak için 'exit' yazın.
        
        while (1) {
            // Kullanıcıdan mesaj al / Get message from user
            printf("Parent> ");
            fflush(stdout);
            
            if (fgets(message, sizeof(message), stdin) == NULL) {
                break;
            }
            
            // Yeni satırı kaldır / Remove newline
            message[strcspn(message, "\n")] = 0;
            
         
            // Çocuğa mesaj gönder / Send message to child
            write(pipe1[1], message, strlen(message) + 1);
            printf("Parent: Sent -> '%s' \n", message);
            //Ebeyn: Gönderildi -> '%s'
            
            // Çocuktan cevap al / Receive response from child
            int bytes_read = read(pipe2[0], buffer, sizeof(buffer));
            if (bytes_read <= 0) {
                printf("  Parent: Child process terminated. \n");
                // Ebeyn: Çocuk proses sonlandı.
                break;
            }
            
            printf("Parent: Received <- '%s'\n\n", buffer);
           
        }
        
        // Pipe'ları kapat / Close pipes
        close(pipe1[1]);
        close(pipe2[0]);
        
        // Çocuk prosesi bekle / Wait for child process
        wait(NULL);
        
        printf("\n=== Parent Program Terminated ===\n");
        
    }
    
    return 0;
}