#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // sleep() için

#define TOTAL_THREADS 10
// tr: Aynı anda en fazla 3 thread'e izin ver / en: Allow max 3 concurrent threads
#define MAX_CONCURRENT_THREADS 3 

// tr: Semaforu tanımla / en: Define the semaphore
sem_t resource_semaphore;

// tr: Thread'lerin çalışacağı fonksiyon / en: Function for the threads
void* use_resource(void* arg) {
    long id = (long)arg;

    printf("[Thread %ld] Waiting to access the resource...\n", id);

    // tr: "Kaynağa" erişmeye çalış (Semafor değerini 1 azalt)
    // tr: Değer 0 ise (yani 3 thread içerideyse), yer açılana kadar burada bekle.
    // en: Try to access the resource (Decrement semaphore value)
    // en: If value is 0 (i.e., 3 threads are inside), wait here.
    sem_wait(&resource_semaphore);

    // --- SINIRLI BÖLGE (Kapasite = 3) ---
    printf("[Thread %ld] ===> ENTERED. Using the resource (2s)...\n", id);
    sleep(2); // tr: Kaynağı kullanıyormuş gibi yap / en: Pretend to use the resource
    printf("[Thread %ld] <=== LEAVING the resource.\n", id);
    // --- SINIRLI BÖLGE BİTİŞİ ---

    // tr: "Kaynaktan" çık (Semafor değerini 1 artır)
    // tr: Bekleyen bir thread'i uyandır.
    // en: Leave the resource (Increment semaphore value)
    // en: Wakes up a waiting thread.
    sem_post(&resource_semaphore);

    return NULL;
}

int main() {
    pthread_t threads[TOTAL_THREADS];

    // tr: Semaforu başlat. Değeri = MAX_CONCURRENT_THREADS (3)
    // en: Initialize the semaphore. Value = MAX_CONCURRENT_THREADS (3)
    sem_init(&resource_semaphore, 0, MAX_CONCURRENT_THREADS);

    printf("[Main] Starting %d threads. Resource capacity is %d.\n",
           TOTAL_THREADS, MAX_CONCURRENT_THREADS);

    for (long i = 0; i < TOTAL_THREADS; i++) {
        pthread_create(&threads[i], NULL, use_resource, (void*)i);
        usleep(100 * 1000); // tr: Thread'leri hafifçe yay / en: Stagger thread creation
    }

    // tr: Tüm thread'lerin bitmesini bekle / en: Wait for all threads to finish
    for (int i = 0; i < TOTAL_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // tr: Semaforu yok et / en: Destroy the semaphore
    sem_destroy(&resource_semaphore);

    printf("[Main] All threads have finished.\n");
    return 0;
}