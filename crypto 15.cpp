#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
void calculate_frequency(const char *ciphertext, int frequency[]) {
    memset(frequency, 0, ALPHABET_SIZE * sizeof(int));
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            frequency[tolower(ciphertext[i]) - 'a']++;
        }
    }
}
void decrypt_with_key(const char *ciphertext, int key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int shifted = tolower(ciphertext[i]) - 'a' - key;
            if (shifted < 0) shifted += ALPHABET_SIZE;
            plaintext[i] = shifted + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
void sort_results(char plaintexts[][100], int scores[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                int temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
                char temp_text[100];
                strcpy(temp_text, plaintexts[j]);
                strcpy(plaintexts[j], plaintexts[j + 1]);
                strcpy(plaintexts[j + 1], temp_text);
            }
        }
    }
}
int main() {
    char ciphertext[100], plaintexts[26][100];
    int frequency[ALPHABET_SIZE], scores[26];
    const char common_letters[] = "etaoinshrdlcumwfgypbvkjxqz"; 
    int top_n;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_n);
    calculate_frequency(ciphertext, frequency);
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decrypt_with_key(ciphertext, key, plaintexts[key]);
        scores[key] = 0;
        for (int i = 0; plaintexts[key][i] != '\0'; i++) {
            char ch = tolower(plaintexts[key][i]);
            if (isalpha(ch)) {
                for (int j = 0; j < 6; j++) {
                    if (ch == common_letters[j]) {
                        scores[key]++;
                    }
                }
            }
        }
    }
    sort_results(plaintexts, scores, ALPHABET_SIZE);
    printf("\nTop %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n && i < ALPHABET_SIZE; i++) {
        printf("%d. %s (Score: %d)\n", i + 1, plaintexts[i], scores[i]);
    }
    return 0;
}