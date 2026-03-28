#ifndef USERS_H_
#define USERS_H_

#include "util.h"

typedef struct {
    char balance;
    char * username;
    char * first_name;
    char * last_name;
    int account_number;
} UserDef;


F_STATUS Create_User (char * username, char * first_name, char * last_name);

#endif // USERS_H_