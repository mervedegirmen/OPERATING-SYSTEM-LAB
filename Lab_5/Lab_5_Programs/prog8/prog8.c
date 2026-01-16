// prog8.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t fork_return_value;

    // tr: fork() çağrılmadan önce, bu kod sadece tek bir proseste çalışır.
    // en: Before fork() is called, this code runs in a single process.
    printf("Program running... Active Program PID %d\n", getpid());

    fork_return_value = fork(); // tr: Proses burada ikiye ayrılır. en: The process splits into two here.
	
    if (fork_return_value < 0) {
        // tr: Hata durumu. Fork bir çocuk proses oluşturamadı.
        // en: Error condition. Fork failed to create a child process.
        fprintf(stderr, "Fork error!\n");
        return 1;
    } else if (fork_return_value == 0) {
        // tr: Bu blok SADECE çocuk proseste çalışır.
        // en: This block is executed ONLY by the child process.
        printf("--> Child Process PID %d, Parent Process PID %d\n", getpid(), getppid());
    } else {
        // tr: Bu blok SADECE ana proseste çalışır.
        // en: This block is executed ONLY by the parent process.
        printf("--> Parent Process PID %d. Created Child Process PID: %d\n", getpid(), fork_return_value);
    }

    return 0;
}