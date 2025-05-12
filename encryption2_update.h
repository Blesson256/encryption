#ifndef SECURE_MESSAGE_H
#define SECURE_MESSAGE_H

#define MESSAGE_MAX_LEN 1024
#define KEY_SIZE 32
#define SALT "I[]aM\';S@lT1nG_t0-m@k3?>1T<53Ur8*!()_Welcome"

typedef struct {
    char content[MESSAGE_MAX_LEN];
    int encrypted;  
} message_t;

void encrypt_message(message_t *message, const char *passkey);
void decrypt_message(message_t *message, const char *passkey);

#endif
