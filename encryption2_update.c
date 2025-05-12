#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secure_message.h"

static void mes_key(const char *input, unsigned char *output, int output_size) {
    unsigned long base_hash = 5381;
    int c;

    while ((c = (unsigned char)*input++)) {
        base_hash = (base_hash * 33) + c;  /* DJB2 Hash */
    }

    for (int i = 0; i < output_size; i++) {
        output[i] = (base_hash >> (i * 5)) & 0xFF;
    }
}

void encrypt_message(message_t *message, const char *passkey) {
    if (!message || !passkey || message->encrypted) {
        return;
    }

    char salt_key[256];
    snprintf(salt_key, sizeof(salt_key), "%s%s", passkey, SALT, message->content);

    unsigned char enc_key[KEY_SIZE];
    mes_key(salt_key, enc_key, KEY_SIZE);

    int msg_len = strlen(message->content);
    for (int i = 0; i < msg_len; i++) {
        message->content[i] ^= enc_key[i % KEY_SIZE];
    }

    message->encrypted = 1;
}

void decrypt_message(message_t *message, const char *passkey) {
    if (!message || !passkey || !message->encrypted) {
        return;
    }

    char salt_key[256];
    snprintf(salt_key, sizeof(salt_key), "%s%s", passkey, SALT, message->content);

    unsigned char dec_key[KEY_SIZE];
    mes_key(salt_key, dec_key, KEY_SIZE);

    int msg_len = strlen(message->content);
    for (int i = 0; i < msg_len; i++) {
        message->content[i] ^= dec_key[i % KEY_SIZE];
    }

    message->encrypted = 0;
}

