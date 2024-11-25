#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
void generate_cipher_alphabet(const char *keyword, char cipher_alphabet[]) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;
    for (int i = 0; i < strlen(keyword); i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            cipher_alphabet[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher_alphabet[index++] = ch;
        }
    }

    cipher_alphabet[index] = '\0';
}
void encrypt(const char *plaintext, const char *cipher_alphabet, char *ciphertext) {
    for (int i = 0; i < strlen(plaintext); i++) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
            int is_upper = isupper(ch);
            int pos = toupper(ch) - 'A';
            ciphertext[i] = is_upper ? cipher_alphabet[pos] : tolower(cipher_alphabet[pos]);
        } else {
            ciphertext[i] = ch;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}
void decrypt(const char *ciphertext, const char *cipher_alphabet, char *plaintext) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            int is_upper = isupper(ch);
            char upper_ch = toupper(ch);
            int pos = 0;
            while (cipher_alphabet[pos] != upper_ch && pos < ALPHABET_SIZE) {
                pos++;
            }

            plaintext[i] = is_upper ? 'A' + pos : 'a' + pos;
        } else {
            plaintext[i] = ch; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
int main() {
    const char *keyword = "CIPHER";
    char cipher_alphabet[ALPHABET_SIZE + 1];
    char plaintext[256];
    char ciphertext[256];
    char decrypted_text[256];
    generate_cipher_alphabet(keyword, cipher_alphabet);
    printf("Keyword: %s\n", keyword);
    printf("Cipher alphabet: %s\n", cipher_alphabet);
    printf("\nEnter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    encrypt(plaintext, cipher_alphabet, ciphertext);
    printf("\nCiphertext: %s\n", ciphertext);
    decrypt(ciphertext, cipher_alphabet, decrypted_text);
    printf("\nDecrypted text: %s\n", decrypted_text);
    return 0;
}