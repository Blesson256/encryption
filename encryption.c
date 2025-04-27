#include<stdio.h>
#include<string.h>
#include "library.h"

void encryption_key(char *lastname, int year, char *key){
       strcpy(key, lastname);
       char year_string[5];
       sprintf(year_string, "%d", year);
       strcat(key, year_string);
}

void xor(char *data, const char *key){
       int i; 
       int msg_len = strlen(data); 
       int key_len = strlen(key);
       for (i = 0; i < msg_len; i++){
              data[i] ^= key[i % key_len];
       }
}

void save_message(char *message, char *key){
       FILE *f = fopen("messages.txt", "a");
       if (f == NULL){
              printf("Error opening file.\n");
              return;
       }
       fprintf(f, "Encrypted Message: %s\n", message);
       fprintf(f, "Recipient Key: %s\n", key);
       fprintf(f, "-----\n"); 
       fclose(f);
}
