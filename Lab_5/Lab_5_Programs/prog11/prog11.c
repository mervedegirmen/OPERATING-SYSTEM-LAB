// prog11.c
#include <stdio.h>
#include <unistd.h>

#define NUM_CHILDREN 3

int main() {
    printf("PARENT: My PID is %d. I will create %d children.\n", getpid(), NUM_CHILDREN);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();
        if (pid == 0) { // Sadece çocuk bu bloğa girer
            printf("  CHILD i -> %d PID -> %d PPID -> %d: Hello! .\n", i, getpid(), getppid());
            sleep(1);
            return 0; // tr: Çocuk işini bitirip çıkar. en: Child finishes its job and exits.
        }
    }
    // tr: Ana proses döngüden sonra devam eder. en: Parent process continues after the loop.
    sleep(3); // tr: Tüm çocukların mesajlarını yazması için bekle. en: Wait for all children to print their messages.
    printf("PARENT: All children created.\n");
    return 0;
}