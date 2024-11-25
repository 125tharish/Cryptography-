#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_TEXT_LENGTH 1000
void generate_key_stream(int *key_stream, int length) {
    for (int i = 0; i < length; i++) {
        key_stream[i] = rand() % 26;  
    }
}
void encrypt(char *plaintext, int *key_stream, int length, char *ciphertext) {
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = (plaintext[i] - 'A' + key_stream[i]) % 26 + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = (plaintext[i] - 'a' + key_stream[i]) % 26 + 'a';
        } else {
            ciphertext[i] = plaintext[i];  
        }
    }
}
void decrypt(char *ciphertext, int *key_stream, int length, char *plaintext) {
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = (ciphertext[i] - 'A' - key_stream[i] + 26) % 26 + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = (ciphertext[i] - 'a' - key_stream[i] + 26) % 26 + 'a';
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
}
int main() {
    srand(time(NULL)); 
    char plaintext[MAX_TEXT_LENGTH];
    char ciphertext[MAX_TEXT_LENGTH];
    char decrypted_text[MAX_TEXT_LENGTH];
    printf("Enter plaintext: ");
    fgets(plaintext, MAX_TEXT_LENGTH, stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;
    int length = strlen(plaintext);
    int key_stream[length];
    generate_key_stream(key_stream, length);
    encrypt(plaintext, key_stream, length, ciphertext);
    ciphertext[length] = '\0';  
    printf("\nCiphertext: ");
    for (int i = 0; i < length; i++) {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
    decrypt(ciphertext, key_stream, length, decrypted_text);
    decrypted_text[length] = '\0'; 
    printf("\nDecrypted text: %s\n", decrypted_text);
    return 0;
}
