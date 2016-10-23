#include <stdio.h>
#include <stdlib.h>
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
    /* insert a new row into the table */
    sprintf(sql, "INSERT INTO %s (PRIME, HASH, BITS) VALUES ('%s', '%s', '%i');", 
        table, lol_sl.prime, lol_sl.hash, lol_sl.bits);
    
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

int lol_sl_get(char *table, char *dbname, char *op, int id) {
    int rc;
    sqlite3 *db;
    db = '\0';
    char *zErrMsg = 0;
    
    //lol_sl_open(dbname, db);
    rc = sqlite3_open(dbname, &db);
    
    char sql[2048];
    /* get a single row by it's id */
    sprintf(sql, "SELECT * FROM %s WHERE id = %i;", 
        table, id);
        
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    
    return 1;
}

int lol_sl_del(char *table, char *dbname, char *op, int id) {
    int rc;
    sqlite3 *db;
    db = '\0';
    char *zErrMsg = 0;
    
    //lol_sl_open(dbname, db);
    rc = sqlite3_open(dbname, &db);
    
    char sql[2048];
    /* delete rows where operator id */
    sprintf(sql, "DELETE FROM %s WHERE id %s %i;", 
        table, op, id);
        
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    
    return 1;
}

int lol_sl_get_all(char *table, char *dbname) {
    int rc;
    sqlite3 *db;
    db = '\0';
    char *zErrMsg = 0;
    
    //lol_sl_open(dbname, db);
    rc = sqlite3_open(dbname, &db);
    
    char sql[2048];
    /* get all the rows from the table */
    sprintf(sql, "SELECT * FROM %s;", 
        table);
        
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    
    return 1;
}


int lol_sl_get_total(char *table, char *dbname, int *total) {
    int rc;
    sqlite3 *db;
    db = '\0';
    char *zErrMsg = 0;
    
    //lol_sl_open(dbname, db);
    rc = sqlite3_open(dbname, &db);
    
    char sql[2048];
    /* get all the rows from the table */
    sprintf(sql, "SELECT COUNT(*) FROM %s;", 
        table);
        
    rc = sqlite3_exec(db, sql, callback_total, total, &zErrMsg);
    
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    
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

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i=0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    return 0; // needs to return 0
}

int callback_total(void *count, int argc, char **argv, char **azColName) {
    int *c = count;
    *c = atoi(argv[0]);
    return 0;
}