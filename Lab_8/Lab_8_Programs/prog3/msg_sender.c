#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define the message structure
// Mesaj yapısını tanımla
struct msg_buffer {
    long msg_type;       // Message type (must be > 0) // Mesaj tipi (0'dan büyük olmalı)
    char msg_text[100];  // Message data // Mesaj verisi
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate unique key
    // Benzersiz anahtar oluştur (touch msgfile)
    key = ftok("msgfile", 65);

    // Create a message queue
    // Bir mesaj kuyruğu oluştur (IPC_CREAT)
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Prepare the message
    // Mesajı hazırla
    message.msg_type = 1; // Set message type to 1 // Mesaj tipini 1 olarak ayarla
    strcpy(message.msg_text, "Hello Message Queue!");

    // Send the message
    // Mesajı gönder
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Sender: Message sent.\n");

    return 0;
}