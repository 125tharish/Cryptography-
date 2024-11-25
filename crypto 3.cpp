#include <stdio.h>
#include <string.h>
void generateTable(char table[5][5], char key[26]) {
    char alphabet[26] = "abcdefghiklmnopqrstuvwxyz";
    int i, j = 0;
    for (i = 0; i < 26; i++) {
        if (strchr(key, alphabet[i]) == NULL) {
            key[j++] = alphabet[i];
        }
    }
    for (i = 0; i < 25; i++) {
        table[i / 5][i % 5] = key[i];
    }
}
void encrypt(char plaintext[100], char table[5][5]) {
    int i;
    for (i = 0; i < strlen(plaintext); i += 2) {
        char a = plaintext[i];
        char b = plaintext[i + 1];
        int row1, row2, col1, col2;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (table[j][k] == a) {
                    row1 = j;
                    col1 = k;
                }
                if (table[j][k] == b) {
                    row2 = j;
                    col2 = k;
                }
            }
        }
        if (row1 == row2) { 
            plaintext[i] = table[row1][(col1 + 1) % 5];
            plaintext[i + 1] = table[row2][(col2 + 1) % 5];
        } else if (col1 == col2) { 
            plaintext[i] = table[(row1 + 1) % 5][col1];
            plaintext[i + 1] = table[(row2 + 1) % 5][col2];
        } else { 
            plaintext[i] = table[row1][col2];
            plaintext[i + 1] = table[row2][col1];
        }
    }
}
int main() {
    char key[26] = "prudvi";
    char plaintext[100] = "instruments";
    char table[5][5];
    generateTable(table, key);
    encrypt(plaintext, table);
    printf("Encrypted Text: %s\n", plaintext);
    return 0;
}