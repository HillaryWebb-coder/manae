#include <stdio.h>

#include "users.h"
#include "db.h"

int main() {
    if (create_db_connection("bank_db") != SUCCESS) {
        fprintf(stderr, "Failed to setup database\n");
        return 1;
    }

    Create_User("hill", "Hillary", "Ogieleguea");

    if (close_db_connection() != SUCCESS) {
        fprintf(stderr, "Failed to close database connection\n");
        return 1;
    }

    return 0;
}