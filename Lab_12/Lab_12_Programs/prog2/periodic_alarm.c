#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
 * TR: SIGALRM sinyali için işleyici (handler) fonksiyonu.
 * EN: The handler function for the SIGALRM signal.
 */
void sigalrm_handler(int signum) {
    printf("Tick...\n");
    
    // TR: Bir sonraki alarmı 2 saniye sonrasına yeniden kur.
    // EN: Re-establish the next alarm for 2 seconds later.
    alarm(2);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigalrm_handler;
    sigemptyset(&sa.sa_mask);
    
    // TR: 'SA_RESTART' bayrağı, pause() gibi kesilen sistem çağrılarının
    // TR: sinyal işleyicisi bittikten sonra otomatik olarak yeniden başlamasını sağlar.
    // EN: The 'SA_RESTART' flag ensures interrupted system calls (like pause())
    // EN: are automatically restarted after the handler finishes.
    // TR: (Bu örnekte 'pause' için gerekli değil ama 'read' gibi fonksiyonlar için önemlidir)
    // EN: (Not essential for 'pause' in this example, but vital for functions like 'read')
    sa.sa_flags = SA_RESTART; 

    // TR: SIGALRM sinyali için 'sa' ayarlarını kaydet.
    // EN: Register the 'sa' settings for the SIGALRM signal.
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("Error setting up sigaction");
        return 1;
    }

    // TR: İlk alarmı 2 saniye sonrasına kur.
    // EN: Set the first alarm for 2 seconds.
    alarm(2);
    
    printf("[Main] Alarm clock started. Using pause() to wait for signals.\n");

    // TR: Sonsuz döngü. pause() bizi bir sonraki sinyale kadar uyutacak.
    // EN: Infinite loop. pause() will put us to sleep until the next signal.
    while (1) {
        pause(); // TR: Sadece bir sinyal gelene kadar bekle.
                 // EN: Wait until any signal is received.
        
        // TR: Program akışı:
        // TR: 1. pause() ile uyu
        // TR: 2. SIGALRM gelir
        // TR: 3. sigalrm_handler çalışır ("Tick..." yazar, yeni alarm(2) kurar)
        // TR: 4. Handler biter
        // TR: 5. pause() sinyal yüzünden döner
        // TR: 6. Döngü başa döner ve tekrar pause() ile uyur (Adım 1)
        
        // EN: Program flow:
        // EN: 1. Sleep with pause()
        // EN: 2. SIGALRM arrives
        // EN: 3. sigalrm_handler runs (prints "Tick...", sets new alarm(2))
        // EN: 4. Handler returns
        // EN: 5. pause() returns due to signal
        // EN: 6. Loop repeats, sleeping at pause() again (Step 1)
    }

    return 0; // TR: Buraya asla ulaşılmaz / EN: Never reached
}