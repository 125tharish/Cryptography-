#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
#define MAX_TEXT 256
void generate_playfair_square(const char *key, char playfair_square[SIZE][SIZE]);
void preprocess_text(char *text);
void find_position(const char playfair_square[SIZE][SIZE], char letter, int *row, int *col);
void encrypt_playfair(const char *plaintext, const char playfair_square[SIZE][SIZE], char *ciphertext);
void print_playfair_square(const char playfair_square[SIZE][SIZE]) {
    printf("Playfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", playfair_square[i][j]);
        }
        printf("\n");
    }
}
int main() {
    char key[] = "MFHIJKUNOPQZVWXYELARGDSTBC";
    char playfair_square[SIZE][SIZE];
    char plaintext[MAX_TEXT] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[MAX_TEXT];
    generate_playfair_square(key, playfair_square);
    print_playfair_square(playfair_square);
    preprocess_text(plaintext);
    encrypt_playfair(plaintext, playfair_square, ciphertext);
    printf("\nPlaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}
void generate_playfair_square(const char *key, char playfair_square[SIZE][SIZE]) {
    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            playfair_square[i][j] = key[index++];
        }
    }
}
void preprocess_text(char *text) {
    int len = strlen(text);
    char result[MAX_TEXT];
    int pos = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            char ch = toupper(text[i]);
            if (ch == 'J') ch = 'I'; 
            result[pos++] = ch;
        }
    }
    for (int i = 0; i < pos; i += 2) {
        if (i + 1 < pos && result[i] == result[i + 1]) {
            memmove(&result[i + 2], &result[i + 1], pos - i - 1);
            result[i + 1] = 'X';
            pos++;
        }
    }
    if (pos % 2 != 0) {
        result[pos++] = 'X';
    }

    result[pos] = '\0';
    strcpy(text, result);
}

// Function to find the position of a letter in the Playfair square
void find_position(const char playfair_square[SIZE][SIZE], char letter, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (playfair_square[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encrypt_playfair(const char *plaintext, const char playfair_square[SIZE][SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    int pos = 0;
    for (int i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = plaintext[i + 1];
        int row1, col1, row2, col2;
        find_position(playfair_square, a, &row1, &col1);
        find_position(playfair_square, b, &row2, &col2);
        if (row1 == row2) {
            ciphertext[pos++] = playfair_square[row1][(col1 + 1) % SIZE];
            ciphertext[pos++] = playfair_square[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[pos++] = playfair_square[(row1 + 1) % SIZE][col1];
            ciphertext[pos++] = playfair_square[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[pos++] = playfair_square[row1][col2];
            ciphertext[pos++] = playfair_square[row2][col1];
        }
    }

    ciphertext[pos] = '\0';
}
