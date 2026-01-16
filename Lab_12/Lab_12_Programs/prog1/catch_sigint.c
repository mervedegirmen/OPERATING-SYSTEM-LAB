#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// TR: Sinyal işleyicisi içinde sadece bu tür değişkenler güvenle kullanılabilir.
// EN: Only variables of this type are safe to use inside a signal handler.
volatile sig_atomic_t interrupt_count = 0;

/*
 * TR: SIGINT (Ctrl+C) sinyali için sinyal işleyici (handler) fonksiyonu.
 * EN: The signal handler function for SIGINT (Ctrl+C).
 */
void sigint_handler(int signum) {
    interrupt_count++;
    
    if (interrupt_count == 1) {
        printf("\n[Handler] Caught SIGINT (1/3). Press Ctrl+C 2 more times to exit.\n");
    } else if (interrupt_count == 2) {
        printf("\n[Handler] Caught SIGINT (2/3). Press Ctrl+C 1 more time to exit.\n");
    } else {
        printf("\n[Handler] Caught SIGINT (3/3). Exiting now.\n");
        exit(0); // TR: Güvenli çıkış / EN: Clean exit
    }
}

int main() {
    // TR: sigaction yapısını sinyal işleyicimizi kurmak için hazırlıyoruz.
    // EN: We prepare the sigaction structure to set up our signal handler.
    struct sigaction sa;
    
    // TR: İşleyici fonksiyonumuzu ata
    // EN: Assign our handler function
    sa.sa_handler = sigint_handler;
    
    // TR: Güvenli olması için tüm sinyal bayraklarını sıfırla
    // EN: Reset all signal flags for safety
    sigemptyset(&sa.sa_mask);
    
    // TR: Ekstra bayrak yok
    // EN: No extra flags
    sa.sa_flags = 0;

    // TR: SIGINT (Ctrl+C) sinyali için 'sa' ayarlarını kaydet.
    // EN: Register the 'sa' settings for the SIGINT (Ctrl+C) signal.
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error setting up sigaction");
        return 1;
    }

    printf("[Main] Process started (PID: %d). Waiting for signals...\n", getpid());
    printf("[Main] Press Ctrl+C to trigger the handler.\n");

    // TR: Programı sonsuza kadar çalışır tut. sleep() sinyal tarafından kesilecektir.
    // EN: Keep the program running indefinitely. sleep() will be interrupted by the signal.
    while (1) {
        sleep(5); // TR: 5 saniye uyu (veya bir sinyal gelene kadar)
                  // EN: Sleep for 5 seconds (or until a signal arrives)
        printf("[Main] ...still waiting...\n");
    }

    return 0; // TR: Buraya asla ulaşılmaz / EN: Never reached
}