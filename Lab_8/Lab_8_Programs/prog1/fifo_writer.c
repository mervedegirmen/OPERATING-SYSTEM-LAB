#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    char message[] = "Hello FIFO! This is the first message.";

    // Create the FIFO (if it doesn't exist)
    // FIFO'yu oluştur (varsa hata verme)
    // 0666: Read/write permissions
    // 0666: Okuma/yazma izinleri
    mkfifo(FIFO_NAME, 0666); 

    printf("Writer: Opening FIFO for writing...\n");
    // Open for writing only (O_WRONLY)
    // Sadece yazma modunda aç (O_WRONLY)
    // This call BLOCKS until a reader opens it
    // Okuyucu açana kadar bu çağrı BLOKLANIR
    fd = open(FIFO_NAME, O_WRONLY); 
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    printf("Writer: Sending message: %s\n", message);
    // Write the message to the FIFO
    // Mesajı FIFO'ya yaz
    // +1 for the null terminator
    // +1 null sonlandırıcı karakter için
    write(fd, message, strlen(message) + 1); 
    
    close(fd);
    printf("Writer: Done.\n");

    return 0;
}