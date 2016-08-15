/*
 *  _            _   _       _ 
 * | | _____   _(_) | | ___ | |
 * | |/ _ \ \ / / | | |/ _ \| |
 * | |  __/\ V /| |_| | (_) | |
 * |_|\___| \_/ |_(_)_|\___/|_|
 *
 * crypt helper library
*/

#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <string.h>

#ifndef LOL_CRYPT
#define LOL_CRYPT

#define LOL_CRYPT_LARGE 8192

/* type to simplify key/iv creation */
typedef struct lol_crypt {
    unsigned char key[LOL_CRYPT_LARGE];
    unsigned char iv[LOL_CRYPT_LARGE];
} lol_crypt;

/* declare functions */
void handleErrors(void);
int lol_crypt_init(void);
int lol_crypt_bytes(int size, unsigned char rb[size]);
int lol_crypt_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);
int lol_crypt_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext);
int lol_crypt_keyiv(int key_size, int iv_size, lol_crypt *lc);
void lol_crypt_cleanup(void);
/* end */

int lol_crypt_keyiv(int key_size, int iv_size, lol_crypt *lc) {
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
        fread(lc->key, LOL_CRYPT_LARGE, LOL_CRYPT_LARGE, key_fp);
    } else {
        /* if key file does not exist */
        key_fp = fopen(fn_key, "w");
        if(key_fp == NULL) {
            printf("ERROR OPENING KEY FILE\n");
        }
        lol_crypt_bytes(key_size, lc->key);
        fwrite(lc->key, 1, sizeof lc->key, key_fp);
    }
    
    if( access( fn_iv, F_OK ) != -1 ) {
        /* if iv file exists */
        iv_fp = fopen(fn_iv, "r");
        if(iv_fp == NULL) {
            printf("ERROR OPENING IV FILE\n");
        }
        fread(lc->iv, LOL_CRYPT_LARGE, LOL_CRYPT_LARGE, iv_fp);
    } else {
        /* if iv file does not exist */
        iv_fp = fopen(fn_iv, "w");
        if(iv_fp == NULL) {
            printf("ERROR OPENING IV FILE\n");
        }
        lol_crypt_bytes(iv_size, lc->iv);
        fwrite(lc->iv, 1, sizeof lc->iv, iv_fp);
    }
    fclose(key_fp);
    fclose(iv_fp);
    return 0;
}
  
int lol_crypt_init(void) {
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);
    return 0;
}

int lol_crypt_bytes(int size, unsigned char rb[size]) {
    if(!RAND_bytes(rb, size)) {
        printf("OpenSSL Error. Ded now.\n");
        return -1;
    }
    return size;
}

int lol_crypt_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext) {
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int lol_crypt_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

void lol_crypt_cleanup(void) {
    /* Clean up */
    EVP_cleanup();
    ERR_free_strings();
}
#endif