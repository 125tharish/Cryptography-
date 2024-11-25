#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 1000
void count_frequencies(const char *text, int freq[]) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalnum(text[i]) || ispunct(text[i])) {
            freq[(unsigned char)text[i]]++;
        }
    }
}
void print_frequencies(const int freq[]) {
    printf("Character frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", i, freq[i]);
        }
    }
}
void apply_substitution(const char *ciphertext, char *plaintext, const char substitution[]) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        char ch = ciphertext[i];
        if (isalnum(ch) || ispunct(ch)) {
            plaintext[i] = substitution[(unsigned char)ch];
        } else {
            plaintext[i] = ch;
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
int main() {
    const char ciphertext[MAX_LENGTH] = "53‡‡†305))6*:4826)41.)41):806*;48+860))85;;]8*::$8+83 (88)5*4:46(;88*96*2;8)(;485);5*+2:(;4956*2(5*4)88  ;4069285);)6+8)4‡‡:1(19:48081;8:811;48485;4)485+528806*81 (19;48;(88;4(†234;48)4;161;:188;12;";
    char plaintext[MAX_LENGTH] = {0};
    int freq[256] = {0};
    char substitution[256];
    for (int i = 0; i < 256; i++) {
        substitution[i] = i;
    }
    count_frequencies(ciphertext, freq);
    print_frequencies(freq);
    substitution['‡'] = 'e'; 
    substitution['†'] = 't'; 
    substitution[';'] = 'h'; 
    apply_substitution(ciphertext, plaintext, substitution);
    printf("\nDeciphered text:\n%s\n", plaintext);
    return 0;
}