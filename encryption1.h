#ifndef SECURE_MESSAGE_H
#define SECURE_MESSAGE_H

#define MESSAGE_MAX_LEN 1024
#define KEY_SIZE 35
#define SALT "S@1tVa1!"

typedef struct {
    char content[MESSAGE_MAX_LEN];
    int encrypted;  
} message_t;

void encrypt_message(message_t *message, const char *passkey);
void decrypt_message(message_t *message, const char *passkey);

#endif
