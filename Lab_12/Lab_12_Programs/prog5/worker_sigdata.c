/* worker_sigdata.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
 * TR: Bu, SA_SIGINFO bayrağı kullanıldığında GEREKLİ olan 3 argümanlı işleyicidir.
 * EN: This is the 3-argument handler REQUIRED when using the SA_SIGINFO flag.
 */
void sigusr1_handler_with_data(int signum, siginfo_t *info, void *context) {
    
    // TR: Bize gönderilen veriyi 'info' yapısından alıyoruz.
    // EN: We retrieve the data sent to us from the 'info' structure.
    int received_value = info->si_value.sival_int;
    pid_t sender_pid = info->si_pid; // TR: Sinyali kimin gönderdiğini de görebiliriz!
                                    // EN: We can also see who sent the signal!

    printf("[Worker PID: %d] Caught SIGUSR1 from sender PID: %d\n", getpid(), sender_pid);
    printf("[Worker PID: %d] Received Data Value (Parameter): %d\n", getpid(), received_value);
    
    // TR: İşimiz bitti, çıkıyoruz.
    // EN: We are done, exiting.
    exit(0);
}

int main() {
    printf("[Worker PID: %d] Started. Waiting for SIGUSR1 with data...\n", getpid());

    struct sigaction sa;
    
    // TR: Tüm yapıyı temizle
    // EN: Clear the whole structure
    sigemptyset(&sa.sa_mask);

    // TR: 3 argümanlı işleyiciyi ata (sa_handler değil, sa_sigaction!)
    // EN: Assign the 3-argument handler (sa_sigaction, not sa_handler!)
    sa.sa_sigaction = sigusr1_handler_with_data;
    
    // TR: En ÖNEMLİ bayrak. Bu, "Veri bekliyorum" anlamına gelir.
    // EN: The MOST IMPORTANT flag. This means "I am expecting data".
    sa.sa_flags = SA_SIGINFO;

    // TR: SIGUSR1 (Kullanıcı Tanımlı Sinyal 1) için 'sa' ayarlarını kaydet.
    // EN: Register the 'sa' settings for the SIGUSR1.
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error setting up sigaction");
        return 1;
    }

    // TR: Sinyal beklerken uyu.
    // EN: Sleep while waiting for a signal.
    while (1) {
        pause(); 
    }

    return 0; 
}