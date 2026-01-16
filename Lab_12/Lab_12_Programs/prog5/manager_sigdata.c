/* manager_sigdata.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    printf("[Manager PID: %d] Manager started.\n", getpid());
    
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (child_pid == 0) {
        /**********************/
        /* TR: ÇOCUK PROSES KODU */
        /* EN: CHILD PROCESS CODE */
        /**********************/
        char *args[] = {"./worker_sigdata", NULL};
        execv(args[0], args);
        
        perror("execv failed"); // TR: Sadece hata durumunda burası çalışır
                               // EN: Only runs on error
        exit(1);

    } else {
        /***********************/
        /* TR: EBEVEYN PROSES KODU */
        /* EN: PARENT PROCESS CODE */
        /***********************/
        
        printf("[Manager PID: %d] Waiting 3 seconds before sending SIGUSR1 + data...\n", getpid());
        sleep(3); // TR: Çocuğun işleyiciyi kurması için zaman tanı
                  // EN: Give child time to set up handler

        // TR: Gönderilecek veriyi (parametre) hazırla.
        // EN: Prepare the data (parameter) to be sent.
        union sigval val_to_send;
        val_to_send.sival_int = 42; // TR: İşte parametremiz! / EN: Here is our parameter!

        printf("[Manager PID: %d] Sending SIGUSR1 with value %d to child %d...\n", 
               getpid(), val_to_send.sival_int, child_pid);
        
        // TR: kill() yerine sigqueue() kullan.
        // EN: Use sigqueue() instead of kill().
        if (sigqueue(child_pid, SIGUSR1, val_to_send) == -1) {
            perror("sigqueue failed");
        }

        int status;
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("[Manager PID: %d] Child exited gracefully with status %d.\n", 
                   getpid(), WEXITSTATUS(status));
        }
        
        printf("[Manager PID: %d] Manager exiting.\n", getpid());
    }

    return 0;
}