#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_MESSAGE_LENGTH 500
#define MAX_KEY_LENGTH 50

void encryption_key(char *lastname, int year, char *key);
void xor(char *data, const char *key);
void save_message(char *message, char *key);

#endif
