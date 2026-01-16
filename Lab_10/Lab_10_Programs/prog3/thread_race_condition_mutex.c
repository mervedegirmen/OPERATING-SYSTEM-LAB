#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define INCREMENTS 1000000

// tr: Paylaşılan global değişken / en: Shared global variable
long global_counter = 0;

// tr: Kritik bölgeyi korumak için Mutex / en: Mutex to protect the critical section
pthread_mutex_t counter_mutex;

// tr: Thread'in çalıştıracağı fonksiyon / en: Function for the thread to run
void* incrementer(void* arg) {
    long thread_id = (long)arg;
    printf("Thread %ld: Starting to increment...\n", thread_id);
    
    for (int i = 0; i < INCREMENTS; i++) {
        
        // tr: Kilidi al / en: Acquire the lock
        pthread_mutex_lock(&counter_mutex);

        // --- KRİTİK BÖLGE BAŞLANGICI / CRITICAL SECTION START ---
        global_counter++; // tr: Bu işlem artık koruma altında / en: This operation is now protected
        // --- KRİTİK BÖLGE BİTİŞİ / CRITICAL SECTION END ---

        // tr: Kilidi bırak / en: Release the lock
        pthread_mutex_unlock(&counter_mutex);
    }
    printf("Thread %ld: Finished incrementing.\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // tr: Mutex'i başlat / en: Initialize the mutex
    pthread_mutex_init(&counter_mutex, NULL);

    printf("[Main] Creating %d threads, each incrementing %d times...\n", NUM_THREADS, INCREMENTS);

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, incrementer, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // tr: Mutex'i yok et / en: Destroy the mutex
    pthread_mutex_destroy(&counter_mutex);

    printf("\n--- Final Result ---\n");
    printf("Expected counter value: %d\n", NUM_THREADS * INCREMENTS);
    printf("Actual counter value:   %ld\n", global_counter);

    if (global_counter == NUM_THREADS * INCREMENTS) {
        printf("Result is CORRECT! Synchronization worked.\n");
    } else {
        // tr: Bu artık olmamalı! / en: This should not happen anymore!
        printf("Result is WRONG! Race Condition occurred!\n");
    }

    return 0;
}