#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_WORKER_THREADS 2
#define TASK_QUEUE_SIZE 10

// tr: Kuyruktaki bir görevi temsil eden yapı / en: Struct representing a task in the queue
typedef struct {
    int task_id; // tr: Görev ID'si / en: Task ID
} Task;

// tr: Görev Kuyruğu / en: Task Queue
Task task_queue[TASK_QUEUE_SIZE];
int task_count = 0;
int queue_head = 0; // tr: Kuyruk başı / en: Queue head
int queue_tail = 0; // tr: Kuyruk sonu / en: Queue tail

// tr: Senkronizasyon araçları / en: Synchronization tools
pthread_mutex_t queue_mutex;
pthread_cond_t queue_cond_non_empty; // tr: Kuyrukta iş var (Tüketici için) / en: Task available (for consumer)
// Not: Gerçek bir pool'da 'queue_cond_non_full' (Üretici için) de olurdu.
// Note: A real pool would also have 'queue_cond_non_full' (for producer).

// tr: İşçi thread'in yapacağı asıl iş / en: The actual work the thread will do
void example_task_function(int task_id) {
    printf("  [Worker] Task %d starting (processing for 1s)...\n", task_id);
    sleep(1);
    printf("  [Worker] Task %d finished.\n", task_id);
}

// tr: İşçi Thread'in ana döngüsü (Tüketici) / en: Main loop for a worker thread (Consumer)
void* worker_main(void* arg) {
    long id = (long)arg;
    printf("[Worker %ld] Started. Waiting for tasks.\n", id);

    while (1) {
        pthread_mutex_lock(&queue_mutex);

        // tr: Kuyrukta iş yoksa bekle / en: If queue is empty, wait
        while (task_count == 0) {
            // tr: Uyandırma beklerken kilidi bırakır / en: Releases lock while waiting
            pthread_cond_wait(&queue_cond_non_empty, &queue_mutex);
        }

        // tr: Kuyruktan bir görev al (Dequeue) / en: Dequeue a task from the head
        Task task = task_queue[queue_head];
        queue_head = (queue_head + 1) % TASK_QUEUE_SIZE;
        task_count--;

        pthread_mutex_unlock(&queue_mutex);

        // tr: Kilidi bıraktıktan sonra görevi çalıştır (ÖNEMLİ!)
        // en: Execute the task *after* releasing the lock (IMPORTANT!)
        printf("[Worker %ld] Picked up task %d.\n", id, task.task_id);
        example_task_function(task.task_id);
    }
    return NULL;
}

// tr: Kuyruğa görev ekleyen fonksiyon (Üretici) / en: Function to add a task (Producer)
void submit_task(Task task) {
    pthread_mutex_lock(&queue_mutex);

    if (task_count >= TASK_QUEUE_SIZE) {
        printf("[Main] Queue is full. Task %d dropped.\n", task.task_id);
        pthread_mutex_unlock(&queue_mutex);
        return;
    }

    // tr: Görevi kuyruğun sonuna ekle (Enqueue) / en: Add task to the tail (Enqueue)
    task_queue[queue_tail] = task;
    queue_tail = (queue_tail + 1) % TASK_QUEUE_SIZE;
    task_count++;

    // tr: Bekleyen bir işçiyi uyandır / en: Signal a waiting worker
    pthread_cond_signal(&queue_cond_non_empty);

    pthread_mutex_unlock(&queue_mutex);
}

int main() {
    pthread_t workers[NUM_WORKER_THREADS];

    pthread_mutex_init(&queue_mutex, NULL);
    pthread_cond_init(&queue_cond_non_empty, NULL);

    // tr: İşçi thread'leri (Tüketiciler) oluştur / en: Create worker threads (Consumers)
    for (long i = 0; i < NUM_WORKER_THREADS; i++) {
        pthread_create(&workers[i], NULL, worker_main, (void*)i);
    }

    // tr: Kuyruğa 5 görev ekle (Üretici) / en: Submit 5 tasks to the queue (Producer)
    printf("[Main] Submitting 5 tasks...\n");
    for (int i = 1; i <= 5; i++) {
        Task t = { .task_id = i };
        submit_task(t);
        printf("[Main] Submitted task %d.\n", i);
        usleep(200 * 1000); // tr: Görev ekleme aralığı / en: Stagger task submission
    }

    // tr: İşçilerin işleri bitirmesi için biraz bekle / en: Wait for workers to process
    printf("[Main] Waiting 10s for tasks to be processed...\n");
    sleep(10); 
    
    printf("[Main] Exiting (workers will be terminated).\n");
    // tr: Gerçek bir pool'da thread'leri düzgün kapatma mekanizması olurdu.
    // en: A real pool would have a proper shutdown mechanism.
    exit(0); 
}