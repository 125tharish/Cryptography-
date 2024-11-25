#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 8
#define KEY_SIZE 24  
void des_encrypt(uint8_t *input, uint8_t *output, uint8_t *key) {
    memcpy(output, input, BLOCK_SIZE);  
}
void triple_des_encrypt(uint8_t *input, uint8_t *output, uint8_t *key) {
    uint8_t temp[BLOCK_SIZE];
    des_encrypt(input, temp, key);          
    des_encrypt(temp, temp, key + 8);        
    des_encrypt(temp, output, key + 16);    
}
void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, int length, uint8_t *key, uint8_t *iv) {
    uint8_t block[BLOCK_SIZE];
    uint8_t xor_block[BLOCK_SIZE];
    memcpy(xor_block, iv, BLOCK_SIZE); 
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] = plaintext[i + j] ^ xor_block[j];
        }
        triple_des_encrypt(block, xor_block, key);
        memcpy(ciphertext + i, xor_block, BLOCK_SIZE);
    }
}
int main() {
    uint8_t key[KEY_SIZE] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,  
        0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67   
    };
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t plaintext[BLOCK_SIZE * 2] = {  
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F,
        0x72, 0x6C, 0x64, 0x21, 0x20, 0x43, 0x42, 0x43
    };
    uint8_t ciphertext[BLOCK_SIZE * 2]; 
    printf("Plaintext:\n");
    for (int i = 0; i < sizeof(plaintext); i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");
    cbc_encrypt(plaintext, ciphertext, sizeof(plaintext), key, iv);
    printf("Ciphertext:\n");
    for (int i = 0; i < sizeof(ciphertext); i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
    return 0;
}
