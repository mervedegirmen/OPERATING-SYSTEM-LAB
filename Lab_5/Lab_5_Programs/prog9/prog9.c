// exercise3_orphan.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Çocuk proses
        // tr: Çocuk proses, ilk başta orijinal ebeveyninin PID'sini yazdırır.
        // en: The child process first prints the PID of its original parent.
        printf("Child Process PID -> %d: Hello! , Parent -> PID %d\n", getpid(), getppid());
        
        sleep(4); // tr: 4 saniye bekle. Bu sırada ana proses çoktan bitmiş olacak. en: Sleep for 4 seconds. The parent will have exited by then.
        
        // tr: Çocuk uyandığında, yeni ebeveyninin (genellikle PID 1) PID'sini yazdırır.
        // en: When the child wakes up, it prints the PID of its new parent (usually PID 1).
        printf("Child Process PID -> %d: Woke up!, Parent -> PID  %d\n", getpid(), getppid());
    } else if (pid > 0) { // Ana proses
        // tr: Ana proses, çocuğu oluşturduktan hemen sonra işini bitirir.
        // en: The parent process finishes its job right after creating the child.
        printf("Parent PID -> %d: I created the child and now I'm leaving. \n", getpid());
    } else {
       fprintf(stderr, "Fork işlemi başarısız oldu!\n");
    }

    return 0;
}
