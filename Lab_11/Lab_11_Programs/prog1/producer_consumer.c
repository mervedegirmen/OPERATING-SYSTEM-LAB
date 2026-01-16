#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// tr: Paylaşılan kaynaklar / en: Shared resources
pthread_mutex_t buffer_mutex;
pthread_cond_t buffer_cond; // tr: İşin hazır olduğunu bildiren sinyal / en: Signal that item is ready
int item_ready = 0; // tr: Koşul (0 = boş, 1 = dolu) / en: The condition (0 = empty, 1 = full)

// tr: Tüketici Thread / en: Consumer Thread
void* consumer(void* arg) {
    printf("[Consumer] Started. Locking mutex to check condition...\n");
    
    pthread_mutex_lock(&buffer_mutex);
    printf("[Consumer] Mutex acquired.\n");

    // tr: İş hazır değilse BEKLE / en: IF item is not ready, WAIT
    // tr: 'while' kullanmak 'if' kullanmaktan daha güvenlidir (Spurious Wakeups)
    // en: Using 'while' is safer than 'if' (due to Spurious Wakeups)
    while (item_ready == 0) {
        printf("[Consumer] Condition (item_ready == 0) is true. Waiting on condition...\n");
        
        // tr: 1. Mutex'i bırakır, 2. Uyur, 3. Uyanınca Mutex'i geri alır
        // en: 1. Releases mutex, 2. Sleeps, 3. Re-acquires mutex on wakeup
        pthread_cond_wait(&buffer_cond, &buffer_mutex);
        
        printf("[Consumer] Woke up! Re-acquired mutex. Checking condition again.\n");
    }

    // --- Kritik Bölge / Critical Section ---
    printf("[Consumer] Condition met (item_ready != 0). Consuming item.\n");
    item_ready = 0; // tr: Tamponu boşalt / en: Mark buffer as empty
    // --- Bitiş / End ---

    pthread_mutex_unlock(&buffer_mutex);
    printf("[Consumer] Released mutex. Finished.\n");
    return NULL;
}

// tr: Üretici Thread / en: Producer Thread
void* producer(void* arg) {
    printf("[Producer] Started. Will produce item in 2s...\n");
    sleep(2); // tr: İşi yapıyormuş gibi yap / en: Pretend to do work

    printf("[Producer] Locking mutex to produce...\n");
    pthread_mutex_lock(&buffer_mutex);

    item_ready = 1; // tr: İşi hazır olarak işaretle / en: Mark item as ready
    printf("[Producer] Item produced (item_ready = 1). Signaling consumer...\n");

    // tr: Tüketiciye sinyal gönder (iş hazır) / en: Signal the consumer (item is ready)
    pthread_cond_signal(&buffer_cond);

    pthread_mutex_unlock(&buffer_mutex);
    printf("[Producer] Released mutex. Finished.\n");
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    pthread_mutex_init(&buffer_mutex, NULL);
    pthread_cond_init(&buffer_cond, NULL);

    // tr: Tüketiciyi önce başlatmak, bekleme (wait) anını net gösterir
    // en: Starting consumer first clearly shows the 'wait' state
    pthread_create(&cons_thread, NULL, consumer, NULL);
    usleep(500 * 1000); // tr: Tüketicinin beklemeye başladığından emin ol / en: Ensure consumer starts waiting
    pthread_create(&prod_thread, NULL, producer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&buffer_cond);

    printf("[Main] All threads finished.\n");
    return 0;
}