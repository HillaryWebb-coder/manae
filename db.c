#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "sqlite3.h"
#include "db.h"
#include "util.h"

static struct db_connection {
    sqlite3 *db;
    char *database_name;
} db_conn;

static sqlite3 * db = NULL;

F_STATUS create_db_connection(char * database_name) {
    db_conn.database_name = database_name;
    int rc = sqlite3_open_v2(database_name, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (rc != SQLITE_OK || db == NULL) {
        fprintf(stderr, "Unable to open database '%s': %s\n", database_name, sqlite3_errmsg(db));
        if (db) sqlite3_close(db);
        db = NULL;
        return ERROR;
    }

    const char *sql_stmt = "CREATE TABLE IF NOT EXISTS users ("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "username TEXT UNIQUE NOT NULL,"
                           "first_name TEXT NOT NULL,"
                           "last_name TEXT NOT NULL,"
                           "balance INTEGER DEFAULT 0" 
                           ");";

    return send_db_command((char *)sql_stmt);
}

F_STATUS open_db_connection(char * database_name) {
    if (db) {
        fprintf(stderr, "Database connection already open\n");
        return ERROR;
    }

    int rc = sqlite3_open_v2(database_name, &db, SQLITE_OPEN_READWRITE, NULL);
    if (rc != SQLITE_OK || db == NULL) {
        fprintf(stderr, "Unable to open database '%s': %s\n", database_name, sqlite3_errmsg(db));
        if (db) sqlite3_close(db);
        db = NULL;
        return ERROR;
    }

    return SUCCESS;
}

F_STATUS send_db_command(char * stmt) {
    if (!db) {
        fprintf(stderr, "No database connection\n");
        return ERROR;
    }

    open_db_connection(db_conn.database_name);

    sqlite3_stmt *ppStmt;
    const char *pzTail = NULL;
    sqlite3_reset(ppStmt);
    int rc = sqlite3_prepare_v2(db, stmt, -1, &ppStmt, &pzTail);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_prepare_v2 failed: %s\n", sqlite3_errmsg(db));
        if (ppStmt) sqlite3_finalize(ppStmt);
        return ERROR;
    }

    if (pzTail && *pzTail != '\0') {
        fprintf(stderr, "Extra SQL after statement: %s\n", pzTail);
        sqlite3_finalize(ppStmt);
        return ERROR;
    }

    rc = sqlite3_step(ppStmt);
    if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
        fprintf(stderr, "sqlite3_step failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(ppStmt);
        return ERROR;
    }

    sqlite3_finalize(ppStmt);
    close_db_connection();
    return SUCCESS;
}

F_STATUS close_db_connection(void) {
    if (db) {
        sqlite3_close(db);
        return SUCCESS;
    }
    return ERROR;
}