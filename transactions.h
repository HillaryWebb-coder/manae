#ifndef TRANSACTIONS_H_
#define TRANSACTIONS_H_

#include <time.h>

typedef enum {CREDIT, DEBIT} TransactionType;

typedef struct {
    TransactionType transaction_type;
    int amount;
    time_t DateTime;    
} TransactionTypeDef

#endif //TRANSACTIONS_H_