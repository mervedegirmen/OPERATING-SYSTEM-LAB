#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    char buffer[100];

    // Create the FIFO (writer might have created it already)
    // FIFO'yu oluştur (yazıcı zaten oluşturmuş olabilir)
    mkfifo(FIFO_NAME, 0666); 

    printf("Reader: Opening FIFO for reading...\n");
    // Open for reading only (O_RDONLY)
    // Sadece okuma modunda aç (O_RDONLY)
    // This call BLOCKS until a writer opens it
    // Yazıcı açana kadar bu çağrı BLOKLANIR
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    printf("Reader: Waiting for message...\n");
    // Read from the FIFO into the buffer
    // FIFO'dan buffer'a oku
    // This call BLOCKS until data is available
    // Veri gelene kadar bu çağrı BLOKLANIR
    read(fd, buffer, sizeof(buffer));

    printf("Reader: Received message: %s\n", buffer);

    close(fd);
    
    // Remove the FIFO file from the system
    // FIFO dosyasını sistemden kaldır
    unlink(FIFO_NAME); 
    printf("Reader: Done and FIFO deleted.\n");

    return 0;
}