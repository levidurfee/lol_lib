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
    
    char *key_base64_e_output;
    char *iv_base64_e_output;
    unsigned char key_read_output[8192];
    unsigned char iv_read_output[8192];
    unsigned char key[key_size];
    unsigned char iv[iv_size];
    unsigned char ciphertext[8192];
    unsigned char decryptedtext[8192];
    
    lol_crypt_init();

    char fn_key[] = ".key";
    char fn_iv[] = ".iv";
    
    /* if key file exists */
    if( access( fn_key, F_OK ) != -1 ) {
        FILE *key_fp_r;
        key_fp_r = fopen(fn_key, "r");
        if(key_fp_r == NULL) {
            printf("ERROR OPENING KEY FILE\n");
        }
        
        fread(key_read_output, 8192, 8192, key_fp_r);
        if(ferror(key_fp_r)) {
            printf("KEY READ ERROR\n");
            return -1;
        }
        
        if( Base64Decode(key_read_output, &key, &key_size) != 0) {
            printf("key decode failed\n");
            return -1;
        }
        
        fclose(key_fp_r);
    } else {
        FILE *key_fp;
        key_fp = fopen(fn_key, "w");
        
        lol_crypt_bytes(key_size, key);
        Base64Encode(key, key_size, &key_base64_e_output);
        fwrite(key_base64_e_output, 1, sizeof key_base64_e_output, key_fp);
        
        fclose(key_fp);
    }
    /* if iv file exists */
    if( access( fn_iv, F_OK ) != -1 ) {
        FILE *iv_fp_r;
        iv_fp_r = fopen(fn_iv, "r");
        
        fread(iv_read_output, 8192, 8192, iv_fp_r);
        if(ferror(iv_fp_r)) {
            printf("IV READ ERROR\n");
            return -1;
        }
        
        if( Base64Decode(iv_read_output, &iv, &iv_size) != 0) {
            printf("iv decode failed\n");
            return -1;
        }
        
        fclose(iv_fp_r);
    } else {
        FILE *iv_fp;
        iv_fp = fopen(fn_iv, "w");
        
        lol_crypt_bytes(iv_size, iv);
        
        Base64Encode(iv, iv_size, &iv_base64_e_output);

        fwrite(iv_base64_e_output, 1, sizeof iv_base64_e_output, iv_fp);
        
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