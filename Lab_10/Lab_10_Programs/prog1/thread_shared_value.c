/*
 * tr: Bu program, paylaşılan bir tamsayı üzerinde yarış durumu
 * oluşturan thread'ler yaratır.
 * en: This program creates threads that have a race condition
 * on a shared integer.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3
// tr: Döngü sayısını artırarak yarış durumu olasılığını artırın
// en: Increase loop count to increase the chance of a race condition
#define LOOP_COUNT 100

// tr: Global (paylaşılan) değişken / en: Global (shared) variable
int shared_value = 0;

void* thread_function(void* arg) {
    long tid = (long)arg;

    for (int i = 0; i < LOOP_COUNT; i++) {

        // --- KRİTİK BÖLGE BAŞLANGICI (ŞU AN KORUMASIZ) ---
        // --- CRITICAL SECTION START (CURRENTLY UNPROTECTED) ---

        shared_value = 1;

        // tr: Normalde bu 'if' ASLA doğru olmamalıdır.
        // en: Normally, this 'if' should NEVER be true.
        if (shared_value == 0) {
             printf("Thread %ld: [%d. iteration] Error: Set Value=1, after if (Value==0) -> true!\n",
                   tid, i);
        }

        shared_value = 0;

        // tr: Normalde bu 'if' ASLA doğru olmamalıdır.
        // en: Normally, this 'if' should NEVER be true.
        if (shared_value == 1) {
            printf("Thread %ld: [%d. iteration] Error: Set Value=0, after if (Value==1) -> true!\n",
                   tid, i);
        }
        
        // --- KRİTİK BÖLGE BİTİŞİ ---
        // --- CRITICAL SECTION END ---
    }

    return NULL;
}

int main(int argc, char** argv) {
    pthread_t thread_ids[NUM_THREADS];
    void* status;

    printf("[Main] Starting %d threads, loop count %d...\n", NUM_THREADS, LOOP_COUNT);

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&thread_ids[i], NULL, thread_function, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(thread_ids[i], &status);
    }

    printf("[Main] All threads finished.\n");
    exit(0);
}