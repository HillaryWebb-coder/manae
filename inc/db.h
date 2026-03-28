#ifndef DB_H_
#define DB_H_

#include "util.h"

F_STATUS create_db_connection(char * database_name);
F_STATUS send_db_command(char * stmt);
F_STATUS close_db_connection(void);

#endif