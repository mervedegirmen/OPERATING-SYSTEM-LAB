// prog7.c
#include <stdio.h>
#include <unistd.h> // tr: getpid() ve getppid() fonksiyonları için gereklidir. en: Required for getpid() and getppid() functions.

int main() {
    // tr: Mevcut prosesin ID'sini al ve ekrana yazdır.
    // en: Get the current process's ID and print it to the screen.
    pid_t current_pid = getpid();
    printf("Program Process ID (PID): %d\n", current_pid);

    // tr: Mevcut prosesin ebeveyninin ID'sini al ve ekrana yazdır.
    // en: Get the parent process's ID and print it to the screen.
    pid_t parent_pid = getppid();
    printf("Program Parent Proses ID (PPID): %d\n", parent_pid);

    return 0;
}