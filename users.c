#include <stdio.h>
#include <stdlib.h>

#include "users.h"
#include "db.h"

F_STATUS Create_User (char * username, char * first_name, char * last_name){
    UserDef newUser;
    newUser.username = username;
    newUser.first_name = first_name;
    newUser.last_name = last_name;
    newUser.balance = 0;

    char sql_stmt[256];
    sprintf(sql_stmt, "INSERT INTO users (username, first_name, last_name) VALUES ('%s', '%s', '%s');", newUser.username, newUser.first_name, newUser.last_name);
    printf("SQL statement: %s\n\r", sql_stmt);
    int rc = send_db_command(sql_stmt);
    if (rc != SUCCESS) {
        fprintf(stderr, "Failed to create user\n");

        return ERROR;
    }

    printf("New user created\n\r");
    printf("%s, %s, %s, balance: %d\n\r", newUser.username, newUser.first_name, newUser.last_name, newUser.balance);
    return SUCCESS;
}