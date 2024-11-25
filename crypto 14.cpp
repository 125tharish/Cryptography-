#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MOD 26
void encrypt(const char *plaintext, const int key[], int key_len, char *ciphertext) {
    int i, shift;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            shift = key[i % key_len];
            ciphertext[i] = ((tolower(plaintext[i]) - 'a' + shift) % MOD) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}
void decrypt(const char *ciphertext, const int key[], int key_len, char *plaintext) {
    int i, shift;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            shift = key[i % key_len];
            plaintext[i] = ((tolower(ciphertext[i]) - 'a' - shift + MOD) % MOD) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}
int main() {
    const char plaintext[] = "send more money";
    const int key_stream[] = {9, 0, 17, 23, 2, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_len = sizeof(key_stream) / sizeof(key_stream[0]);
    char ciphertext[100];
    encrypt(plaintext, key_stream, key_len, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    const char target_plaintext[] = "cash not needed";
    const char *given_ciphertext = ciphertext;
    int derived_key_stream[100];
    char decrypted_text[100];
    for (int i = 0; target_plaintext[i] != '\0'; i++) {
        if (isalpha(target_plaintext[i])) {
            derived_key_stream[i] = ((tolower(given_ciphertext[i]) - 'a') - (tolower(target_plaintext[i]) - 'a') + MOD) % MOD;
        } else {
            derived_key_stream[i] = 0;
        }
    }
    printf("Derived Key Stream: ");
    for (int i = 0; target_plaintext[i] != '\0'; i++) {
        if (isalpha(target_plaintext[i])) {
            printf("%d ", derived_key_stream[i]);
        }
    }
    printf("\n");
    decrypt(given_ciphertext, derived_key_stream, strlen(target_plaintext), decrypted_text);
    printf("Decrypted Text: %s\n", decrypted_text);
    return 0;
}
