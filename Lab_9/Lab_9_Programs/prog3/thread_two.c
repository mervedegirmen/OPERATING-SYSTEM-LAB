#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * @brief Task 1: Counts from 1 to 5, with 1-second pauses.
 * Görev 1: 1 saniye aralıklarla 1'den 5'e kadar sayar.
 */
void* count_up(void *arg) {
    // This thread's function
    // Bu thread'in fonksiyonu
    printf("[Counter] Thread started.\n");
    
    for (int i = 1; i <= 5; i++) {
        printf("[Counter] Count: %d\n", i);
        // Wait 1 second
        // 1 saniye bekle
        sleep(1);
    }
    
    printf("[Counter] Thread finished.\n");
    return NULL;
}

/**
 * @brief Task 2: Prints letters 'A' to 'E', with 2-second pauses.
 * Görev 2: 2 saniye aralıklarla 'A'dan 'E'ye harfleri basar.
 */
void* print_letters(void *arg) {
    // This thread's function
    // Bu thread'in fonksiyonu
    printf("[Letters] Thread started.\n");
    
    char letters[] = "ABCDE";
    for (int i = 0; i < 5; i++) {
        printf("[Letters] Letter: %c\n", letters[i]);
        // Wait 2 seconds
        // 2 saniye bekle
        sleep(2);
    }
    
    printf("[Letters] Thread finished.\n");
    return NULL;
}

int main() {
    // Thread IDs
    // Thread ID'leri
    pthread_t thread1_id, thread2_id;

    printf("[Main] Starting two different threads...\n");

    // Create the first thread, telling it to run 'count_up'
    // İlk thread'i oluştur, 'count_up' fonksiyonunu çalıştıracağını söyle
    if (pthread_create(&thread1_id, NULL, count_up, NULL) != 0) {
        perror("Failed to create thread 1");
    }

    // Create the second thread, telling it to run 'print_letters'
    // İkinci thread'i oluştur, 'print_letters' fonksiyonunu çalıştıracağını söyle
    if (pthread_create(&thread2_id, NULL, print_letters, NULL) != 0) {
        perror("Failed to create thread 2");
    }

    printf("[Main] Threads created. Waiting for them to join...\n");
    
    // Wait for thread 1 to finish
    // Thread 1'in bitmesini bekle
    pthread_join(thread1_id, NULL);
    printf("[Main] Counter thread (1) has joined.\n");

    // Wait for thread 2 to finish
    // Thread 2'nin bitmesini bekle
    pthread_join(thread2_id, NULL);
    printf("[Main] Letters thread (2) has joined.\n");

    printf("[Main] All threads finished. Exiting.\n");
    return 0;
}
}