#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 26
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; 
}
int determinant_mod(int matrix[2][2]) {
    int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;
    if (det < 0)
        det += MOD;
    return det;
}
int inverse_matrix(int matrix[2][2], int inverse[2][2]) {
    int det = determinant_mod(matrix);
    int det_inv = mod_inverse(det, MOD);
    if (det_inv == -1)
        return 0; 
    inverse[0][0] = (matrix[1][1] * det_inv) % MOD;
    inverse[0][1] = (-matrix[0][1] * det_inv + MOD) % MOD;
    inverse[1][0] = (-matrix[1][0] * det_inv + MOD) % MOD;
    inverse[1][1] = (matrix[0][0] * det_inv) % MOD;
    return 1;
}
void matrix_multiply(int a[2][2], int b[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
            result[i][j] %= MOD;
        }
    }
}
void derive_key(int plaintext[2][2], int ciphertext[2][2], int key[2][2]) {
    int inverse[2][2];
    if (!inverse_matrix(plaintext, inverse)) {
        printf("Error: Plaintext matrix is not invertible modulo 26.\n");
        return;
    }
    matrix_multiply(ciphertext, inverse, key);
}
void print_matrix(int matrix[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int plaintext[2][2] = {{7, 4}, {11, 15}};    
    int ciphertext[2][2] = {{14, 10}, {24, 25}};   
    int key[2][2];
    printf("Plaintext Matrix:\n");
    print_matrix(plaintext);
    printf("Ciphertext Matrix:\n");
    print_matrix(ciphertext);
    derive_key(plaintext, ciphertext, key);
    printf("Derived Key Matrix:\n");
    print_matrix(key);
    return 0;
}