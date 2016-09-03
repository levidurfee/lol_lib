#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../libz/lol_crypt.h"
#define  MAX_LEN  80

int main(void) {
    int key_size = 512;
    int iv_size = 128;
    int ct_len;
    int dt_len;
        
    unsigned char key[key_size];
    unsigned char iv[iv_size];
    unsigned char ciphertext[LOL_CRYPT_LARGE];
    unsigned char decryptedtext[LOL_CRYPT_LARGE];
    
    lol_crypt_init(); /* needs to be run first */
    lol_crypt lc; /* declare a new lol_crypt type */
    lol_crypt_keyiv(key_size, iv_size, &lc); /* create key/iv */
        
    unsigned char *plaintext =
                (unsigned char *)"Lorem ipsum dolor sit amet, no mel ferrn\n \
                eleifend.";
    ct_len = lol_crypt_encrypt(plaintext, strlen ((char *)plaintext), lc.key, lc.iv,
                            ciphertext);
    printf("Ciphertext is:\n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ct_len);
    
    dt_len = lol_crypt_decrypt(ciphertext, ct_len, lc.key, lc.iv, decryptedtext);
    decryptedtext[dt_len] = '\0';
    /* Show the decrypted text */
    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);
    
    /* TODO: move to lol_crypt (ability to read and write files) */
    unsigned char toenc[LOL_CRYPT_LARGE];
    FILE *fp;
    fp = fopen("test_files/to.enc", "r");
    if(fp == NULL) {
        printf("ERROR OPENING to.enc FILE\n");
    }
    fread(toenc, 10000, 1, fp);
    fclose(fp);
    ct_len = lol_crypt_encrypt(toenc, strlen ((char *)toenc), lc.key, lc.iv,
                            ciphertext);
    printf("Ciphertext is:\n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ct_len);
    
    BIO *out;
    out = BIO_new_file("test_files/out.enc", "w");
    if (!out) {
        printf("ERROR IN WRITING OUT.ENC FILE\n");
    }
    BIO_printf(out, ciphertext);
    BIO_free(out);
    
    dt_len = lol_crypt_decrypt(ciphertext, ct_len, lc.key, lc.iv, decryptedtext);
    decryptedtext[dt_len] = '\0';
    /* Show the decrypted text */
    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);
    /* END TODO */
    
    lol_crypt_cleanup();
    return 0;
}