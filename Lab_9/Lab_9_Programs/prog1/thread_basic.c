#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// This is the function that the new thread will execute
// Bu, yeni thread'in çalıştıracağı fonksiyondur
void* thread_function(void *arg) {
    // (void*)arg is unused in this simple example
    // (void*)arg bu basit örnekte kullanılmıyor
    
    printf("Thread: Hello! I am the new thread.\n");
    sleep(2); // Simulate some work // Bir miktar iş simülasyonu
    printf("Thread: I am finishing.\n");
    
    // Threads return a void pointer
    // Thread'ler bir void pointer döndürür
    return NULL;
}

int main() {
    // This variable will hold the ID of the new thread
    // Bu değişken, yeni thread'in ID'sini tutacak
    pthread_t thread_id;
    int error;

    printf("Main: Before creating thread.\n");

    // Create a new thread that will execute 'thread_function'
    // 'thread_function' fonksiyonunu çalıştıracak yeni bir thread oluştur
    error = pthread_create(&thread_id, NULL, thread_function, NULL);
    if (error != 0) {
        // Error handling
        // Hata yönetimi
        fprintf(stderr, "Error creating thread: %d\n", error);
        exit(1);
    }

    printf("Main: After creating thread. Waiting for it to finish...\n");

    // Wait for the thread to complete (similar to wait() for processes)
    // Thread'in tamamlanmasını bekle (prosesler için wait() benzeri)
    pthread_join(thread_id, NULL);

    printf("Main: Thread has finished. Exiting main.\n");

    return 0;
}