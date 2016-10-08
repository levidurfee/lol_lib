#include <stdio.h>
#include <sqlite3.h>
#include "lol_sqlite.h"

int lol_sl_add(char *table, char *dbname, lol_sl lol_sl) {
    int rc;
    sqlite3 *db;
    db = '\0';
    char *zErrMsg = 0;
    
    //lol_sl_open(dbname, db);
    rc = sqlite3_open(dbname, &db);
    
    lol_sl_create(table, db);
    
    char sql[2048];
    sprintf(sql, "INSERT INTO %s (prime) VALUES ('%s');", 
        table, lol_sl.prime);
    
    //printf("%s\n", sql);
    
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "INSERT SQL error: %i %s\n", rc, sqlite3_errmsg(db));
        sqlite3_free(zErrMsg);
    } else {
        //printf("INSERT SUCCESS\n");
    }
    
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

int lol_sl_create(char *table, sqlite3 *db) {
    int rc;
    const char *sql;
    char *zErrMsg = 0;
    /* 
    * this table is hard coded 
    * i would like to have the table created based on the struct
    */
    sql = "CREATE TABLE IF NOT EXISTS test_table ("  \
         "id INTEGER PRIMARY KEY AUTOINCREMENT, " \
         "prime TEXT NOT NULL);";
         
    //printf("%s\n", sql);

    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "CREATE SQL error: %i %s\n", rc, sqlite3_errmsg(db));
        sqlite3_free(zErrMsg);
    } else {
        //fprintf(stdout, "Table created successfully\n");
    }
    return 1;
}

int lol_sl_open(char *dbname, sqlite3 *db) {
    int rc;
    char *zErrMsg = 0;
    
    rc = sqlite3_open(dbname, &db);
    
    if( rc != SQLITE_OK ){
        fprintf(stderr, "OPEN SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table opened\n");
    }
    return 1;
}
