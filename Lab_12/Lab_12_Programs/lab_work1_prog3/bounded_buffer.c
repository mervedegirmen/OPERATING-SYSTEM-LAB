#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20 // TR: Toplam 20 ürün üretilip tüketilecek / EN: Total 20 items will be produced and consumed

// TR: Paylaşılan kaynaklar
// EN: Shared resources
int buffer[BUFFER_SIZE];
int count = 0; // TR: Tampondaki mevcut öğe sayısı / EN: Current number of items in buffer
int in = 0;    // TR: Üreticinin yazacağı indeks / EN: Index where producer will write
int out = 0;   // TR: Tüketicinin okuyacağı indeks / EN: Index where consumer will read

pthread_mutex_t mutex;
// TR: Tampon doluyken üreticinin beklemesi için
// EN: For the producer to wait when the buffer is full
pthread_cond_t cond_full;  
// TR: Tampon boşken tüketicinin beklemesi için
// EN: For the consumer to wait when the buffer is empty
pthread_cond_t cond_empty; 

void *producer_thread(void *arg) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        pthread_mutex_lock(&mutex);

        // TR: Kural 1: Tampon doluysa bekle. 'while' kullanmak zorunludur (Spurious Wakeups).
        // EN: Rule 1: If buffer is full, wait. Using 'while' is mandatory (Spurious Wakeups).
        while (count == BUFFER_SIZE) {
            printf("[Producer] Buffer FULL. Waiting...\n");
            // TR: Mutex'i bırakır ve cond_full sinyalini bekler
            // EN: Releases the mutex and waits for the cond_full signal
            pthread_cond_wait(&cond_full, &mutex); 
        }

        // TR: Tampona veri ekle
        // EN: Add data to the buffer
        buffer[in] = i;
        printf("[Producer] Produced item %d at index %d\n", i, in);
        in = (in + 1) % BUFFER_SIZE; // TR: Dairesel tampon indeksi / EN: Circular buffer index
        count++;

        // TR: Kural 2'yi bekleyen (uyuyan) tüketici varsa uyandır.
        // EN: Wake up a sleeping consumer (waiting on Rule 2), if any.
        pthread_cond_signal(&cond_empty);
        
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 1); // TR: İsteğe bağlı yavaşlatma / EN: Optional slowdown
    }
    return NULL;
}

void *consumer_thread(void *arg) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        pthread_mutex_lock(&mutex);

        // TR: Kural 2: Tampon boşsa bekle.
        // EN: Rule 2: If buffer is empty, wait.
        while (count == 0) {
            printf("\t[Consumer] Buffer EMPTY. Waiting...\n");
            // TR: Mutex'i bırakır ve cond_empty sinyalini bekler
            // EN: Releases the mutex and waits for the cond_empty signal
            pthread_cond_wait(&cond_empty, &mutex);
        }

        // TR: Tampondan veri al
        // EN: Consume data from the buffer
        int item = buffer[out];
        printf("\t[Consumer] Consumed item %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // TR: Dairesel tampon indeksi / EN: Circular buffer index
        count--;

        // TR: Kural 1'i bekleyen (uyuyan) üretici varsa uyandır.
        // EN: Wake up a sleeping producer (waiting on Rule 1), if any.
        pthread_cond_signal(&cond_full);

        pthread_mutex_unlock(&mutex);
        sleep(rand() % 2); // TR: Tüketici daha yavaş / EN: Consumer is slower
    }
    return NULL;
}

int main() {
    pthread_t producer, consumer;

    // TR: Mutex ve Koşul Değişkenlerini başlat
    // EN: Initialize Mutex and Condition Variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_full, NULL);
    pthread_cond_init(&cond_empty, NULL);

    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&consumer, NULL, consumer_thread, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    // TR: Kaynakları temizle
    // EN: Clean up resources
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_full);
    pthread_cond_destroy(&cond_empty);

    printf("[Main] All items produced and consumed.\n");
    return 0;
}