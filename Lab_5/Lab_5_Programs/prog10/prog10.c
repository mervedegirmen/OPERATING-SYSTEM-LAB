// exercise4_wait.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // tr: wait() fonksiyonu için gereklidir. en: Required for the wait() function.

int main() {
    pid_t pid = fork();
    int status;

    if (pid == 0) { // Çocuk proses
        printf("CHILD Process: Working for 3 seconds...\n");
        sleep(3);
        printf("CHILD Process: Work is done, exiting with status code 5.\n");
        exit(5); // tr: Çocuk 5 durum koduyla sonlanıyor. en: Child exits with status code 5.
    } else if (pid > 0) { // Ana proses
        printf("PARENT Process: Waiting for the child process to finish...\n");
        
        // tr: wait() çağrısı, bir çocuk proses bitene kadar ana prosesi bloklar.
        // en: The wait() call blocks the parent process until a child has terminated.
        pid_t terminated_child_pid = wait(&status);
        
        printf("PARENT Process: Child process with PID %d has terminated.\n", terminated_child_pid);

        // tr: WIFEXITED makrosu, çocuğun normal bir şekilde (exit() çağrısıyla) sonlanıp sonlanmadığını kontrol eder.
        // en: The WIFEXITED macro checks if the child terminated normally (via a call to exit()).
        if (WIFEXITED(status)) {
            // tr: WEXITSTATUS makrosu, çocuğun çıkış kodunu alır.
            // en: The WEXITSTATUS macro retrieves the child's exit code.
            int exit_status = WEXITSTATUS(status);
            printf("PARENT Process: The child process's exit status was %d\n", exit_status);
        }
    } else {
       fprintf(stderr, "Fork failed!\n");
    }

    return 0;
}