/*
 *  _            _   _       _ 
 * | | _____   _(_) | | ___ | |
 * | |/ _ \ \ / / | | |/ _ \| |
 * | |  __/\ V /| |_| | (_) | |
 * |_|\___| \_/ |_(_)_|\___/|_|
 *
 * prime helper library
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>

void lol_primes(char *r_string, int bits) {
    BIGNUM *r;
    /* thanks https://www.grc.com/otg/uheprng.htm */
    static const char rnd_seed[] = "k5kgM<F)75OCSFSkSkrh)MIVVn+&uO$L \
                                    I_r0Q3*Tp6wNg>}:[Ol3D!5/o`MhczJ8 \
                                    ]'?qhu1U'}xyD7x5>$Re(JB.^0|;fGX_ \
                                    82Tk7G)CNLCE+(^m|KFOMJa!0SFbdR@7 \
                                    e.k-.g#[!5d*w<[O2_v#|;yKXM,{L?oE \
                                    &SU_l}A,^f||A}',$f}e*cwRRG+C~N8< \
                                    3|p#wNuG4r$lVD]]$!j)W--+sWUzBdQp \
                                    t-h#oF&$O>|K]]wLxx2|fNm>-w[:N\v#";

    r = BN_new();
    RAND_seed(rnd_seed, sizeof rnd_seed);
    BN_generate_prime_ex(r, bits, 0, NULL, NULL, NULL);
    strcpy(r_string, BN_bn2dec(r));

    BN_free(r);
}