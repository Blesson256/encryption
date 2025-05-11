#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "secure_message.h"

static void mes_hash(const char *input, unsigned char *output, int size) {
    unsigned long base_hash = 5381;
    int c;

    while ((c = (unsigned char)*input++)) {
        base_hash = ((base_hash << 5) + base_hash) + c;  /* DJB2 Hash */
    }

    for (int i = 0; i < size; i++) {
        output[i] = (base_hash >> (i * 5)) & 0xFF;
    }
}

void encrypt_message(message_t *message, const char *passkey) {
    if (!message || !passkey || message->encrypted) {
        return;
    }

    char salted[256];
    snprintf(salted, sizeof(salted), "%s%s", passkey, SALT);

    unsigned char key[KEY_SIZE];
    mes_hash(salted, key, KEY_SIZE);

    int len = strlen(message->content);
    for (int i = 0; i < len; i++) {
        message->content[i] ^= key[i % KEY_SIZE];
    }

    message->encrypted = 1;
}

void decrypt_message(message_t *message, const char *passkey) {
    if (!message || !passkey || !message->encrypted) {
        return;
    }

    char salted[256];
    snprintf(salted, sizeof(salted), "%s%s", passkey, SALT);

    unsigned char key[KEY_SIZE];
    mes_hash(salted, key, KEY_SIZE);

    int len = strlen(message->content);
    for (int i = 0; i < len; i++) {
        message->content[i] ^= key[i % KEY_SIZE];
    }

    message->encrypted = 0;
}

