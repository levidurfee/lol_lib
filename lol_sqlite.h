#include <sqlite3.h>

typedef struct {
    int id;
    char *prime;
} lol_sl;

int lol_sl_add(char *table, char *dbname, lol_sl lol_sl);
int lol_sl_get(char *table, char *dbname, int id);
int lol_sl_del(char *table, char *dbname, int id);

int lol_sl_get_total(char *table, char *dbname);

int lol_sl_open(char *dbname, sqlite3 *db);
