#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key;
    int shmid;
    char *data;

    // ftok to generate same key
    // Aynı anahtarı oluşturmak için ftok
    key = ftok("shmfile", 65);

    // Access the existing memory segment (no IPC_CREAT)
    // Mevcut bellek segmentine eriş (IPC_CREAT yok)
    shmid = shmget(key, 1024, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the segment to our data space
    // Segmenti adres alanımıza bağla
    data = (char*) shmat(shmid, (void*)0, 0);
    if (data == (char*)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Read data from shared memory
    // Paylaşımlı bellekten veriyi oku
    printf("Reader: Data read from memory: '%s'\n", data);

    // Detach the shared memory segment
    // Paylaşımlı bellek segmentini çöz
    shmdt(data);

    // Mark the segment to be destroyed
    // Segmenti silinmek üzere işaretle
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}