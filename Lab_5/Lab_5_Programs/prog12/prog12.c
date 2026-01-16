// prog12.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3

int main() {
    printf("PARENT: Creating %d children...\n", NUM_CHILDREN);

    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (fork() == 0) { // Çocuk proses
            printf("  CHILD i -> %d PID -> %d: Starting work.\n", i, pid());
            sleep(i + 1); // tr: Her çocuk farklı süre çalışsın. en: Each child works for a different duration.
            printf("  CHILD i -> %d PID -> %d: Finished.\n", i, pid());
            return 0;
        }
    }

    printf("PARENT: All children are running. Now, I will wait for them.\n");

    for (int i = 0; i < NUM_CHILDREN; i++) {
        // tr: Her wait() çağrısı, biten bir çocuğu yakalar.
        // en: Each call to wait() reaps one terminated child.
        pid_t terminated_pid = wait(NULL);
        printf("PARENT: Child with PID %d has finished.\n", terminated_pid);
    }

    printf("PARENT: All my children have finished. Exiting.\n");
    return 0;
}