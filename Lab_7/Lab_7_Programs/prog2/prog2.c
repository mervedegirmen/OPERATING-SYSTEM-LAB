// write() sistem çağrısı ile stdout'a yazma
// Writing to stdout using write() system call

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    char message1[] = "This message was written with write()\n";
    
    
    char message2[] = "File descriptor: 1 (STDOUT_FILENO)\n";
 
    
    // stdout'a yaz (dosya tanımlayıcısı 1)
    // Write to stdout (file descriptor 1)
    write(STDOUT_FILENO, message1, strlen(message1));
    write(1, message2, strlen(message2));  // Aynı şey / Same thing
    
    return 0;
}