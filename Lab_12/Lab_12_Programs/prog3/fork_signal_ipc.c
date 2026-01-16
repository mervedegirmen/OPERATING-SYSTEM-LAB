#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * TR: SIGUSR1 sinyali için işleyici (sadece Çocuk proseste kullanılacak).
 * EN: Handler for SIGUSR1 (will only be used in the Child process).
 */
void sigusr1_handler(int signum) {
    printf("[Child PID: %d] Received SIGUSR1 signal from parent!\n", getpid());
}

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        /**********************/
        /* TR: ÇOCUK PROSES KODU */
        /* EN: CHILD PROCESS CODE */
        /**********************/
        
        printf("[Child PID: %d] Child created. Setting up handler and waiting...\n", getpid());

        // TR: Sinyal işleyiciyi kur
        // EN: Set up the signal handler
        struct sigaction sa;
        sa.sa_handler = sigusr1_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGUSR1, &sa, NULL);

        // TR: Ebeveynden sinyal gelene kadar uyu
        // EN: Sleep until a signal arrives from the parent
        pause();

        printf("[Child PID: %d] Handler finished. Exiting.\n", getpid());
        exit(0);

    } else {
        /***********************/
        /* TR: EBEVEYN PROSES KODU */
        /* EN: PARENT PROCESS CODE */
        /***********************/
        
        printf("[Parent PID: %d] Parent created child (PID: %d).\n", getpid(), pid);
        
        // TR: Çocuğun sinyal işleyiciyi kurmasına zaman tanımak için 2sn bekle
        // EN: Wait 2s to give the child time to set up its handler
        sleep(2); 

        printf("[Parent PID: %d] Sending SIGUSR1 to child %d...\n", getpid(), pid);
        
        // TR: Çocuğa sinyal gönder
        // EN: Send the signal to the child
        if (kill(pid, SIGUSR1) == -1) {
            perror("kill failed");
        }

        // TR: Çocuğun bitmesini bekle (zombi prosesleri önle)
        // EN: Wait for the child to finish (prevents zombie processes)
        wait(NULL);
        
        printf("[Parent PID: %d] Child process finished. Exiting.\n", getpid());
    }

    return 0;
}