#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MOD 26
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; 
}
void matrix_multiply(int key[2][2], int pair[2], int result[2]) {
    result[0] = (key[0][0] * pair[0] + key[0][1] * pair[1]) % MOD;
    result[1] = (key[1][0] * pair[0] + key[1][1] * pair[1]) % MOD;
}
int find_inverse_matrix(int key[2][2], int inverse[2][2]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
    if (det < 0)
        det += MOD;
    int det_inv = mod_inverse(det, MOD);
    if (det_inv == -1)
        return 0; 
    inverse[0][0] = (key[1][1] * det_inv) % MOD;
    inverse[0][1] = (-key[0][1] * det_inv + MOD) % MOD;
    inverse[1][0] = (-key[1][0] * det_inv + MOD) % MOD;
    inverse[1][1] = (key[0][0] * det_inv) % MOD;
    return 1; 
}
void encrypt(const char *plaintext, int key[2][2], char *ciphertext) {
    int pair[2], result[2];
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        pair[0] = plaintext[i] - 'a';
        pair[1] = plaintext[i + 1] - 'a';
        matrix_multiply(key, pair, result);
        ciphertext[i] = (result[0] + 'a');
        ciphertext[i + 1] = (result[1] + 'a');
    }
    ciphertext[len] = '\0';
}
void decrypt(const char *ciphertext, int key[2][2], char *plaintext) {
    int pair[2], result[2];
    int inverse[2][2];
    int len = strlen(ciphertext);

    if (!find_inverse_matrix(key, inverse)) {
        printf("Error: Key matrix is not invertible modulo 26.\n");
        return;
    }
    for (int i = 0; i < len; i += 2) {
        pair[0] = ciphertext[i] - 'a';
        pair[1] = ciphertext[i + 1] - 'a';
        matrix_multiply(inverse, pair, result);
        plaintext[i] = (result[0] + 'a');
        plaintext[i + 1] = (result[1] + 'a');
    }
    plaintext[len] = '\0';
}
int main() {
    int key[2][2] = {{6, 5}, {7, 6}};
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclockx";
    char ciphertext[100], decrypted[100];
    printf("Original Plaintext: %s\n", plaintext);
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, key, decrypted);
    printf("Decrypted Text: %s\n", decrypted);
    return 0;
}