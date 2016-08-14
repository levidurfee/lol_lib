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
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];
    
    lol_crypt_init();
    
    RAND_bytes(key, key_size);
    RAND_bytes(iv, iv_size);
    
    unsigned char *plaintext =
                (unsigned char *)"The quick brown fox jumps over the lazy dog";
    
    ct_len = encrypt(plaintext, strlen ((char *)plaintext), key, iv,
                            ciphertext);
    
    printf("Ciphertext is:\n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ct_len);
    
    dt_len = decrypt(ciphertext, ct_len, key, iv, decryptedtext);
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