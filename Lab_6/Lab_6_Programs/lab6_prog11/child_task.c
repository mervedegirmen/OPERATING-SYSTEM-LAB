#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Child: PID = %d, Parent PID = %d\n", getpid(), getppid());
    // Çocuk: PID = %d, Ebeveyn PID = %d
    
    printf("Child: Performing task...\n");
    // Çocuk: Görev gerçekleştiriliyor...
    
    sleep(2);
    
    printf("Child: Task completed\n");
    // Çocuk: Görev tamamlandı
    
    printf("Child: Returning value 42\n");
    // Çocuk: 42 değeri döndürülüyor
    
    return 42;
}