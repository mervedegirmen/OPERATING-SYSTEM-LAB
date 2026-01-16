// Alt program - Ana program ile mesajlaşma
// Child program - Messaging with parent program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int read_fd, write_fd;
    char buffer[100];
    char response[100];
    
    // Komut satırı argümanlarını kontrol et
    // Check command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <read_fd> <write_fd> \n", argv[0]);
        // Kullanım: %s <read_fd> <write_fd>
        exit(1);
    }
    
    // Dosya tanımlayıcılarını al / Get file descriptors
    read_fd = atoi(argv[1]);   // Ebeynden okuma / Read from parent
    write_fd = atoi(argv[2]);  // Ebeyne yazma / Write to parent
    
    printf("Child [PID: %d]: Program started \n\n", getpid());
    // Çocuk [PID: %d]: Program başlatıldı
    
    while (1) {
        // Ebeynden mesaj al / Receive message from parent
        int bytes_read = read(read_fd, buffer, sizeof(buffer));
        
        if (bytes_read <= 0) {
            break;
        }
        
        
        // Kullanıcıdan cevap al / Get response from user
        printf("Child > ");
        fflush(stdout);
        
        if (fgets(response, sizeof(response), stdin) == NULL) {
            break;
        }
        
        // Yeni satırı kaldır / Remove newline
        response[strcspn(response, "\n")] = 0;
        
        // Ebeyne cevap gönder / Send response to parent
        write(write_fd, response, strlen(response) + 1);
    }
    
    // Dosya tanımlayıcılarını kapat / Close file descriptors
    close(read_fd);
    close(write_fd);
    
    printf("\n=== Child Program Terminated ===\n");
 
    
    return 0;
}