#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

// TR: Paylaşılan kaynaklar
// EN: Shared resources
pthread_mutex_t barrier_mutex;
pthread_cond_t barrier_cond;
int threads_at_barrier = 0; // TR: Bariyere ulaşan thread sayısı / EN: Number of threads at the barrier

// TR: Tüm thread'lerin bariyere ulaşmasını bekleyen fonksiyon
// EN: Function to make threads wait at the barrier
void wait_at_barrier(int id) {
    pthread_mutex_lock(&barrier_mutex);
    
    threads_at_barrier++; // TR: Bariyere ulaştım. / EN: I have reached the barrier.
    printf("[Thread %d] Reached barrier, waiting (%d/%d).\n", id, threads_at_barrier, NUM_THREADS);

    if (threads_at_barrier < NUM_THREADS) {
        // TR: Henüz herkes gelmedi, bekle.
        // EN: Not everyone has arrived yet, wait.
        pthread_cond_wait(&barrier_cond, &barrier_mutex);
    } else {
        // TR: Ben son thread'im. Herkesi uyandır!
        // EN: I am the last thread. Wake everyone up!
        printf("[Thread %d] LAST thread arrived. Opening barrier!\n", id);
        threads_at_barrier = 0; // TR: Bariyeri sıfırla (tekrar kullanılabilir) / EN: Reset barrier (reusable)
        
        // TR: Bekleyen TÜM thread'leri uyandır.
        // EN: Wake up ALL waiting threads.
        pthread_cond_broadcast(&barrier_cond);
    }
    
    // TR: Bariyerden geçiş
    // EN: Passing the barrier
    pthread_mutex_unlock(&barrier_mutex);
    
    printf("[Thread %d] ... Passed barrier, resuming critical work.\n", id);
}

// TR: Her thread'in çalıştıracağı fonksiyon
// EN: Function each thread will execute
void* thread_function(void* arg) {
    int id = *(int*)arg;
    
    // TR: 1. AŞAMA: Bireysel iş
    // EN: STAGE 1: Individual work
    printf("[Thread %d] Doing individual work (0-3s)...\n", id);
    sleep(rand() % 4);

    // TR: 2. AŞAMA: Senkronizasyon (Bariyer)
    // EN: STAGE 2: Synchronization (Barrier)
    wait_at_barrier(id);
    
    // TR: 3. AŞAMA: Senkronize iş (Tüm thread'ler aynı anda burada başlar)
    // EN: STAGE 3: Synchronized work (All threads start here together)
    
    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    
    pthread_mutex_init(&barrier_mutex, NULL);
    pthread_cond_init(&barrier_cond, NULL);
    
    srand(time(NULL));

    printf("[Main] Creating %d threads...\n", NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, thread_function, (void*)id);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&barrier_mutex);
    pthread_cond_destroy(&barrier_cond);

    printf("[Main] All threads have finished their work.\n");
    return 0;
}