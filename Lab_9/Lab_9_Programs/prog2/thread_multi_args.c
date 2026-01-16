#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5

// Thread function
// Thread fonksiyonu
void* thread_function(void *arg) {
    // Cast the void pointer argument back to an integer
    // Void pointer argümanını tekrar integer'a cast et
    // We use intptr_t for a safe cast from pointer to integer
    // Pointer'dan integer'a güvenli cast için intptr_t kullanıyoruz
    long thread_id = (long)arg;

    printf("Thread %ld: Starting work.\n", thread_id);
    // Simulate work with a random sleep
    // Rastgele bir uyku ile iş simülasyonu
    sleep((rand() % 3) + 1);
    printf("Thread %ld: Finishing.\n", thread_id);
    
    return NULL;
}

int main() {
    // Array to hold thread IDs
    // Thread ID'lerini tutmak için dizi
    pthread_t thread_ids[NUM_THREADS];
    long i;

    // --- Creation Loop ---
    // --- Oluşturma Döngüsü ---
    printf("Main: Creating %d threads...\n", NUM_THREADS);
    for (i = 0; i < NUM_THREADS; i++) {
        // (void*)i: Pass the integer 'i' as a void pointer
        // (void*)i: 'i' tamsayısını bir void pointer olarak gönder
        if (pthread_create(&thread_ids[i], NULL, thread_function, (void*)i) != 0) {
            perror("pthread_create");
        }
    }

    printf("Main: All threads created. Waiting for them to join...\n");

    // --- Join Loop ---
    // --- Bekleme (Join) Döngüsü ---
    // We must wait for *all* threads to finish
    // *Tüm* thread'lerin bitmesini beklemeliyiz
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(thread_ids[i], NULL);
        printf("Main: Thread %ld has joined.\n", i);
    }

    printf("Main: All threads have finished. Exiting.\n");
    return 0;
}