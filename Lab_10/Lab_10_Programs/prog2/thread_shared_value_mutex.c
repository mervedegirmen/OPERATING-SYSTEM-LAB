/*
 * tr: Bu program, paylaşılan bir tamsayı üzerindeki yarış durumunu
 * çözmek için MUTEX kullanan thread'ler yaratır.
 * en: This program creates threads that use a MUTEX to solve
 * the race condition on a shared integer.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10
#define LOOP_COUNT 100000 

int shared_value = 0;

// tr: Mutex'i global olarak tanımla / en: Define the mutex globally
pthread_mutex_t value_lock;

void* thread_function(void* arg) {
    long tid = (long)arg;

    for (int i = 0; i < LOOP_COUNT; i++) {

        // tr: Kilidi al (Kritik Bölgeye gir)
        // en: Acquire the lock (Enter Critical Section)
        pthread_mutex_lock(&value_lock);

        // --- KRİTİK BÖLGE BAŞLANGICI (KORUMALI) ---
        // --- CRITICAL SECTION START (PROTECTED) ---

        shared_value = 1;

        if (shared_value == 0) {
            // tr: Bu mesaj ARTIK ASLA görünmemeli
            // en: This message should NOW NEVER appear
            printf("Thread %ld: [%d. iteration] Error: Set Value=1, after if (Value==0) -> true!\n",
                   tid, i);
        }

        shared_value = 0;

        if (shared_value == 1) {
            // tr: Bu mesaj ARTIK ASLA görünmemeli
            // en: This message should NOW NEVER appear
          printf("Thread %ld: [%d. iteration] Error: Set Value=0, after if (Value==1) -> true!\n",
                   tid, i);
        }
        
        // --- KRİTİK BÖLGE BİTİŞİ ---
        // --- CRITICAL SECTION END ---

        // tr: Kilidi bırak (Kritik Bölgeden çık)
        // en: Release the lock (Exit Critical Section)
        pthread_mutex_unlock(&value_lock);
    }

    return NULL;
}

int main(int argc, char** argv) {
    pthread_t thread_ids[NUM_THREADS];
    void* status;

    // tr: Mutex'i başlat / en: Initialize the mutex
    if (pthread_mutex_init(&value_lock, NULL) != 0) {
        printf("\n Mutex init failed\n");
        return 1;
    }

    printf("[Main] Starting %d threads, loop count %d...\n", NUM_THREADS, LOOP_COUNT);

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&thread_ids[i], NULL, thread_function, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(thread_ids[i], &status);
    }

    // tr: Mutex'i yok et / en: Destroy the mutex
    pthread_mutex_destroy(&value_lock);

    printf("[Main] All threads finished.\n");
    exit(0);
}