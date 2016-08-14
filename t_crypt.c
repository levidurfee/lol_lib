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
        FILE *key_fp_r;
        key_fp_r = fopen(fn_key, "r");
        if(key_fp_r == NULL) {
            printf("ERROR OPENING KEY FILE\n");
        }
        
        fread(key, 8192, 8192, key_fp_r);
        
        fclose(key_fp_r);
    } else {
        FILE *key_fp;
        key_fp = fopen(fn_key, "w");
        
        lol_crypt_bytes(key_size, key);
  
        fwrite(key, 1, sizeof key, key_fp);
        
        fclose(key_fp);
    }
    /* if iv file exists */
    if( access( fn_iv, F_OK ) != -1 ) {
        FILE *iv_fp_r;
        iv_fp_r = fopen(fn_iv, "r");
        
        fread(iv, 8192, 8192, iv_fp_r);
        
        fclose(iv_fp_r);
    } else {
        FILE *iv_fp;
        iv_fp = fopen(fn_iv, "w");
        
        lol_crypt_bytes(iv_size, iv);

        fwrite(iv, 1, sizeof iv, iv_fp);
        
        fclose(iv_fp);
    }
        
    unsigned char *plaintext =
                (unsigned char *)"Lorem ipsum dolor sit amet, no mel ferri eleifend. Duis expetendis dissentiet nam id, sed malorum referrentur te, ut magna copiosae sed. Cum ut accusamus sadipscing, ea splendide dissentiunt deterruisset sea, vim semper viderer verterem an. Eu mel epicuri abhorreant. Solum mundi duo id, cu quo liber saperet electram.  Cum lorem legimus accusam ex, ut quo dicat labores. Ea probo aperiri vim, hinc reprehendunt no sit. Suas tempor veritus eum ea. Accumsan deserunt consulatu duo id, iuvaret sanctus et eos, vel et choro graeco electram.  Ei errem vitae eos, probo consetetur vel ad, in ridens perfecto duo. Mea alii eruditi hendrerit et, vix ad melius deterruisset, fabellas urbanitas eam ad. At sed elitr menandri, ex nam novum oratio percipitur. Magna iisque ut sit, usu te vidisse accommodare, cum petentium persequeris eu. Duo eu inani semper accommodare, quot eius repudiare ut pro, iisque apeirian mnesarchum mea no.";
    
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