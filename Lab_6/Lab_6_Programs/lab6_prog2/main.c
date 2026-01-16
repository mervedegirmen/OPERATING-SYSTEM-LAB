#include <stdio.h>
#include <unistd.h>

int main() {
    printf("=== Main Program Started ===\n");
    // === Ana Program Başladı ===
    
    printf("PID: %d\n", getpid());
    printf("About to execute another program...\n");
    // Başka bir program çalıştırılmak üzere...
    
    // Execute the cat command to display a file
    // Bir dosyayı görüntülemek için cat komutunu çalıştır
    execl("/bin/cat", "cat", "/etc/hostname", NULL);
    
    // If we reach here, exec failed
    // Buraya ulaşırsak, exec başarısız oldu
    perror("Exec failed");
    return 1;
}