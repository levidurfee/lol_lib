#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

    char fn_key[] = ".key";
    char fn_iv[] = ".iv";
    
    /* if key file exists */
    if( access( fn_key, F_OK ) != -1 ) {
        FILE *key_fp;
        key_fp = fopen(fn_key, "r");
        fread(key, key_size, 1, key_fp);
        printf("Key read\n");
        fclose(key_fp);
    } else {
        FILE *key_fp;
        key_fp = fopen(fn_key, "w");
        lol_crypt_bytes(key_size, key);
        fwrite(key, 1, key_size, key_fp);
        printf("Key write\n");
        fclose(key_fp);
    }
    /* if iv file exists */
    if( access( fn_iv, F_OK ) != -1 ) {
        FILE *iv_fp;
        iv_fp = fopen(fn_iv, "r");
        fread(iv, iv_size, 1, iv_fp);
        printf("Iv read\n");
        fclose(iv_fp);
    } else {
        FILE *iv_fp;
        iv_fp = fopen(fn_iv, "w");
        lol_crypt_bytes(iv_size, iv);
        fwrite(iv, 1, iv_size, iv_fp);
        printf("Iv write\n");
        fclose(iv_fp);
    }
    
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