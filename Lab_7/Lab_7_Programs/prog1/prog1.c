// read() sistem çağrısı ile stdin'den veri okuma
// Reading data from stdin using read() system call

#include <stdio.h>
#include <unistd.h>

int main() {
    char buffer[100];
    int bytes_read;
    
    printf("Enter a text: ");
 
    // stdin'den oku (dosya tanımlayıcısı 0)
    // Read from stdin (file descriptor 0)
    bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';  // Null terminator ekle / Add null terminator
        printf("Read %d bytes: %s", bytes_read, buffer);
   
    }
    
    return 0;
}