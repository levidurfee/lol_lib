#include <stdio.h>
#include <sqlite3.h>
#include "lol_sqlite.h"

int lol_sl_add(char *table, char *dbname, lol_sl lol_sl) {
    int rc;
    sqlite3 *db;
    db = '\0';                  // initialize the pointer
    lol_sl_open(dbname, db);
    
    // add insert statement
    
    sqlite3_close(db);
    return 1;
}

int lol_sl_get(char *table, char *dbname, int id) {
    return 1;
}

int lol_sl_del(char *table, char *dbname, int id) {
    return 1;
}


int lol_sl_get_total(char *table, char *dbname) {
    return 1;
}

int lol_sl_open(char *dbname, sqlite3 *db) {
    int rc;
    rc = sqlite3_open(dbname, &db);
    if(rc) {
        printf("Couldn't open db\n");
        return -1;
    }
    return 1;
}
