#lab6_prog4
#include <stdio.h>
#include <unistd.h>

int main() {
    // Array of arguments (must end with NULL)
    // Argüman dizisi (NULL ile bitmeli)
    char *args[] = {
        "ls",
        "-l",
        "-a",
        "/home",
        NULL  // Must be NULL terminated / NULL ile sonlandırılmalı
    };
    
    printf("Executing ls with multiple arguments using execv\n");
    // execv kullanarak birden fazla argümanla ls çalıştırılıyor
    
    execv("/bin/ls", args);
    
    // Only executed if execv fails
    // Sadece execv başarısız olursa çalıştırılır
    perror("execv failed");
    return 1;
}