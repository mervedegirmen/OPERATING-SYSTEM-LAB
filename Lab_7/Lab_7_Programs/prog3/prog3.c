// stderr'e hata mesajları yazma
// Writing error messages to stderr

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
    // 1. fprintf() ile stderr'e yazma / Writing to stderr with fprintf()
    fprintf(stderr, "ERROR: This is an error message\n");
   
    
    // 2. write() ile stderr'e yazma / Writing to stderr with write()
    char error_msg[] = "UYARI: Düşük seviye hata mesajı\n";
    // WARNING: Low-level error message
    write(STDERR_FILENO, error_msg, strlen(error_msg));
    
    // 3. perror() ile sistem hatası yazma / Writing system error with perror()
    FILE *file = fopen("no_file.txt", "r");
    if (file == NULL) {
        perror("File opening error");
        
    }
    
    // Normal çıktı stdout'a gider / Normal output goes to stdout
    printf("This is a normal message (stdout))\n");

    
    return 0;
}
