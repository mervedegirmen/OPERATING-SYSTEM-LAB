#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Use the same message structure
// Aynı mesaj yapısını kullan
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate same key
    // Aynı anahtarı oluştur
    key = ftok("msgfile", 65);

    // Access the existing message queue
    // Mevcut mesaj kuyruğuna eriş
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Receive the message
    // Mesajı al
    // 4th arg (1): receive only messages of type 1
    // 4. argüman (1): sadece tipi 1 olan mesajları al
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    printf("Receiver: Message received: '%s'\n", message.msg_text);

    // Destroy the message queue
    // Mesaj kuyruğunu sil
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}