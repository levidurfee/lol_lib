#ifndef LOL_HASH_H
#define LOL_HASH_H
#include <openssl/md5.h>
#include <openssl/sha.h>
#define MAX_LEN 2048
char *lol_md5(const char *str, int length);
int lol_sha(char *hash);
#endif
