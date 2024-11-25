#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char *text, int shift) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            if (isupper(text[i])) {
                text[i] = 'A' + (text[i] - 'A' + shift) % 26;
            } else {
                text[i] = 'a' + (text[i] - 'a' + shift) % 26;
            }
        }
    }
}
void decrypt(char *text, int shift) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            if (isupper(text[i])) {
                text[i] = 'A' + (text[i] - 'A' - shift + 26) % 26;
            } else {
                text[i] = 'a' + (text[i] - 'a' - shift + 26) % 26;
            }
        }
    }
}
int main() {
    char text[100];
    int shift;
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    printf("Enter the shift (1-25): ");
    scanf("%d", &shift);
    
    printf("Original Text: %s\n", text);
    encrypt(text, shift);
    printf("Encrypted Text: %s\n", text);
    decrypt(text, shift);
    printf("Decrypted Text: %s\n", text);
    
    return 0;
}