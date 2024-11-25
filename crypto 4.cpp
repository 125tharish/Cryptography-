#include <stdio.h>
#include <string.h>
void encrypt(char *plaintext, char *key) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        char shift = key[i % strlen(key)] - 'a';
        plaintext[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
    }
}
void decrypt(char *ciphertext, char *key) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        char shift = key[i % strlen(key)] - 'a';
        ciphertext[i] = 'a' + (ciphertext[i] - 'a' - shift + 26) % 26;
    }
}
int main() {
    char plaintext[100] = "tharish";
    char key[26] = "reddy";
    printf("Original Text: %s\n", plaintext);
    encrypt(plaintext, key);
    printf("Encrypted Text: %s\n", plaintext);
    decrypt(plaintext, key);
    printf("Decrypted Text: %s\n", plaintext);
    return 0;
}