#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key;
    int shmid;
    char *data;

    // ftok to generate unique key
    // Benzersiz bir anahtar oluşturmak için ftok kullanılır
    // Create an empty file "shmfile" first: touch shmfile
    // Önce "shmfile" adında boş bir dosya oluşturun: touch shmfile
    key = ftok("shmfile", 65);

    // Create a shared memory segment (1024 bytes)
    // 1024 byte'lık bir paylaşımlı bellek segmenti oluştur (IPC_CREAT)
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the segment to our data space
    // Segmenti prosesin adres alanına bağla (attach)
    data = (char*) shmat(shmid, (void*)0, 0);
    if (data == (char*)(-1)) {
        perror("shmat");
        exit(1);
    }

    printf("Writer: Writing to shared memory...\n");
    // Write data to the shared memory
    // Paylaşımlı belleğe veri yaz
    strcpy(data, "This is a message from shared memory.");

    printf("Writer: Data written. Waiting for reader...\n");
    
    // Detach the shared memory segment
    // Paylaşımlı bellek segmentini çöz (detach)
    shmdt(data);

    return 0;
}