#include <stdio.h>
#include <sqlite3.h>

typedef struct {
    int id;
    char *prime;
    char *hash;
} lol_sl;

int lol_sl_add(char *table, char *dbname, lol_sl lol_sl);
int lol_sl_get(char *table, char *dbname, char *op, int id);
int lol_sl_del(char *table, char *dbname, char *op, int id);

int lol_sl_get_all(char *table, char *dbname);
int lol_sl_get_total(char *table, char *dbname, int *total);

int lol_sl_create(char *table, sqlite3 *db);

int lol_sl_open(char *dbname, sqlite3 *db);

int callback(void *NotUsed, int argc, char **argv, char **azColName);
int callback_total(void *count, int argc, char **argv, char **azColName);
