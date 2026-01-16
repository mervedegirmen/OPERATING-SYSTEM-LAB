#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int i;
    
    // Print parent process information
    // Ana süreç bilgilerini yazdır
    printf("Parent program: PID: %d  PPID: %d\n", getpid(), getppid());
    
    printf("Parent program: Calling exec\n");
    // Ana program: Exec çağrılıyor
    
    // Execute the child program
    // Alt programı çalıştır
    i = execl("./child", "child_program", NULL);
    
    // This line only executes if exec fails
    // Bu satır sadece exec başarısız olursa çalışır
    perror("exec failed");
    
    printf("Parent program: Did we return?\n");
    // Ana program: Dönüş oldu mu?
    
    return 0;
}