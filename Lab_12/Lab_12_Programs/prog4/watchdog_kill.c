#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

// TR: Sinyal işleyicisi tarafından erişilebilmesi için global (ve volatile) olmalı.
// EN: Must be global (and volatile) to be accessed by the signal handler.
volatile pid_t child_pid = 0;

/*
 * TR: SIGALRM işleyicisi. Zamanlayıcı dolduğunda çalışır.
 * EN: SIGALRM handler. Runs when the timer expires.
 */
void sigalrm_handler(int signum) {
    printf("[Handler] Alarm! Time is up. Sending SIGKILL to child %d.\n", child_pid);
    
    // TR: Çocuğu zorla sonlandır. SIGKILL yoksayılamaz veya yakalanamaz.
    // EN: Forcefully terminate the child. SIGKILL cannot be ignored or caught.
    if (child_pid > 0) {
        kill(child_pid, SIGKILL);
    }
}

int main() {
    // TR: SIGALRM için sinyal işleyiciyi kur.
    // EN: Set up the signal handler for SIGALRM.
    struct sigaction sa;
    sa.sa_handler = sigalrm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; // TR: Ekstra bayrak yok / EN: No extra flags
    
    // TR: SIGALRM (alarm sinyali) için işleyiciyi kaydet
    // EN: Register the handler for SIGALRM (alarm signal)
    sigaction(SIGALRM, &sa, NULL);

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
        
        printf("[Child PID: %d] Running in a deliberate infinite loop...\n", getpid());
        
        // TR: Tepkisiz bir prosesi simüle et (CPU'yu meşgul eder)
        // EN: Simulate an unresponsive process (eats CPU)
        while (1) {
            // TR: Kasıtlı olarak boş.
            // EN: Intentionally blank.
        }
        
        // TR: Buraya asla ulaşılamaz
        // EN: Never reached
        printf("[Child PID: %d] Exiting (This should not happen).\n", getpid());
        exit(0);

    } else {
        /***********************/
        /* TR: EBEVEYN PROSES KODU */
        /* EN: PARENT PROCESS CODE */
        /***********************/
        
        printf("[Parent PID: %d] Watching child %d. Setting 3-second alarm.\n", getpid(), child_pid);
        
        // TR: 3 saniyelik "sonlandırma" zamanlayıcısını kur
        // EN: Set the 3-second "termination" timer
        alarm(3);

        int status;
        // TR: Çocuğun bitmesini bekle. Bu, alarm tarafından kesilene kadar
        // TR: (veya çocuk bir şekilde çıkana kadar) bloke olacaktır.
        // EN: Wait for the child to finish. This will block until the alarm
        // EN: handler triggers the child's death (or if the child exits somehow).
        wait(&status);

        // TR: Artık ihtiyaç kalmadığı için alarmı iptal et.
        // EN: Cancel the alarm since it's no longer needed.
        alarm(0); 

        // TR: Çocuğun sinyal ile öldürülüp öldürülmediğini kontrol et.
        // EN: Check if the child was terminated by a signal.
        if (WIFSIGNALED(status)) {
            printf("[Parent PID: %d] Child was terminated by signal %d (SIGKILL).\n", getpid(), WTERMSIG(status));
        } else if (WIFEXITED(status)) {
            // TR: Bu senaryoda bu olmamalı
            // EN: This should not happen in this scenario
            printf("[Parent PID: %d] Child exited normally.\n", getpid());
        }
        
        printf("[Parent PID: %d] Watchdog job finished. Exiting.\n", getpid());
    }

    return 0;
}