#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libz/lol_crypt.h"

int main(void) {
    int key_size = 512;
    int iv_size = 128;
    int ct_len;
    int dt_len;
    
    unsigned char key[key_size];
    unsigned char iv[iv_size];
    unsigned char ciphertext[8192];
    unsigned char decryptedtext[8192];
    
    lol_crypt_init();
    
    lol_crypt_bytes(key_size, key);
    lol_crypt_bytes(iv_size, iv);
    
    unsigned char *plaintext =
                (unsigned char *)"The quick brown fox jumps over the lazy dog";
    
    ct_len = lol_crypt_encrypt(plaintext, strlen ((char *)plaintext), key, iv,
                            ciphertext);
    
    printf("Ciphertext is:\n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ct_len);
    
    dt_len = lol_crypt_decrypt(ciphertext, ct_len, key, iv, decryptedtext);
    decryptedtext[dt_len] = '\0';

    /* Show the decrypted text */
    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);

    /* Clean up */
    EVP_cleanup();
    ERR_free_strings();
    //decrypt(ct_len, ciphertext, *key, *iv);
    return 0;
}