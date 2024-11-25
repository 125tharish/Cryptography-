#include <stdio.h>
#include <string.h>
#include <ctype.h>
int modularInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}
void affineDecrypt(char ciphertext[], int a, int b) {
    int a_inv = modularInverse(a, 26); 
    if (a_inv == -1) {
        printf("Error: a (%d) has no modular inverse under mod 26.\n", a);
        return;
    }
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            int c = ch - base;
            int p = (a_inv * (c - b + 26)) % 26;
            ciphertext[i] = base + p;
        }
    }
}
int main() {
    char ciphertext[100];
    int a, b;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 
    a = 7; 
    b = 23;
    affineDecrypt(ciphertext, a, b);
    printf("Decrypted plaintext: %s\n", ciphertext);
    return 0;
}
