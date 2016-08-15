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
    
    lol_crypt lc;
    
    lol_crypt_keyiv(key_size, iv_size, &lc);
        
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
    
    ct_len = lol_crypt_encrypt(plaintext, strlen ((char *)plaintext), lc.key, lc.iv,
                            ciphertext);
    
    printf("Ciphertext is:\n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ct_len);
    
    dt_len = lol_crypt_decrypt(ciphertext, ct_len, lc.key, lc.iv, decryptedtext);
    decryptedtext[dt_len] = '\0';

    /* Show the decrypted text */
    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);

    /* Clean up */
    EVP_cleanup();
    ERR_free_strings();
    return 0;
}