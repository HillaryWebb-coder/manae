#include <stdio.h>

#include "util.h" 
#include "transactions.h"

F_STATUS new_transaction (TransactionType transaction_type, int amount) {
    TransactionTypeDef transaction;

    transaction.transaction_type = transaction_type;
    transaction.amount = amount;
}