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
    unsigned char ciphertext[LOL_CRYPT_LARGE];
    unsigned char decryptedtext[LOL_CRYPT_LARGE];
    
    lol_crypt_init();

    char fn_key[] = ".key";
    char fn_iv[] = ".iv";
    
    FILE *key_fp;
    FILE *iv_fp;
    
    if( access( fn_key, F_OK ) != -1 ) {
        /* if key file exists */
        key_fp = fopen(fn_key, "r");
        if(key_fp == NULL) {
            printf("ERROR OPENING KEY FILE\n");
        }
        fread(key, LOL_CRYPT_LARGE, LOL_CRYPT_LARGE, key_fp);
    } else {
        /* if key file does not exist */
        key_fp = fopen(fn_key, "w");
        if(key_fp == NULL) {
            printf("ERROR OPENING KEY FILE\n");
        }
        lol_crypt_bytes(key_size, key);
        fwrite(key, 1, sizeof key, key_fp);
    }
    
    if( access( fn_iv, F_OK ) != -1 ) {
        /* if iv file exists */
        iv_fp = fopen(fn_iv, "r");
        if(iv_fp == NULL) {
            printf("ERROR OPENING IV FILE\n");
        }
        fread(iv, LOL_CRYPT_LARGE, LOL_CRYPT_LARGE, iv_fp);
    } else {
        /* if iv file does not exist */
        iv_fp = fopen(fn_iv, "w");
        if(iv_fp == NULL) {
            printf("ERROR OPENING IV FILE\n");
        }
        lol_crypt_bytes(iv_size, iv);
        fwrite(iv, 1, sizeof iv, iv_fp);
    }
    fclose(key_fp);
    fclose(iv_fp);
        
    unsigned char *plaintext =
                (unsigned char *)"Lorem ipsum dolor sit amet, no mel ferrn\n \
                eleifend. Duis expetendis dissentiet nam id, sed malorum r\n \
                eferrentur te, ut magna copiosae sed. Cum ut accusamus sad\n \
                ipscing, ea splendide dissentiunt deterruisset sea, vim se\n \
                mper viderer verterem an. Eu mel epicuri abhorreant. Solum\n \
                mundi duo id, cu quo liber saperet electram.  Cum lorem le\n \
                gimus accusam ex, ut quo dicat labores. Ea probo aperiri v\n \
                im, hinc reprehendunt no sit. Suas tempor veritus eum ea. \n \
                Accumsan deserunt consulatu duo id, iuvaret sanctus et eos\n \
                , vel et choro graeco electram.  Ei errem vitae eos, probo\n \
                consetetur vel ad, in ridens perfecto duo. Mea alii erudit\n \
                i hendrerit et, vix ad melius deterruisset, fabellas urban\n \
                itas eam ad. At sed elitr menandri, ex nam novum oratio pe\n \
                rcipitur. Magna iisque ut sit, usu te vidisse accommodare,\n \
                cum petentium persequeris eu. Duo eu inani semper accommod\n \
                are, quot eius repudiare ut pro, iisque apeirian mnesarchu\n \
                m mea no.";
    
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
    return 0;
}