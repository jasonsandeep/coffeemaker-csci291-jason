#include <stdio.h>

#define INITIAL_BALANCE 2000
#define MAX_TRANSACTIONS 20


void processTransactions(int transactions[], int numTransactions) {
    int balance = INITIAL_BALANCE;
    int tobeprocessed[MAX_TRANSACTIONS];
    int tobeprocessedCount = 0;

    printf("Initial balance: %d AED\n", balance);

    for (int i = 0; i < numTransactions; i++) {
        int transaction = transactions[i];

       
        if (transaction < 0 && balance + transaction < 0) {
            printf("Transaction %d AED is invalid: Insufficient funds. Transaction skipped.\n", transaction);
            tobeprocessed[tobeprocessedCount++] = transaction; 
        }

        else {
            balance += transaction;
            printf("Transaction %d AED processed. New balance: %d AED\n", transaction, balance);

            if (balance <= 0) {
                printf("Balance has reached 0 AED. Stopping further transactions.\n");
                tobeprocessed[tobeprocessedCount++] = transaction;
                break; 
            }
        }
    }

    
    printf("\nFinal balance: %d AED\n", balance);

   
    if (tobeprocessedCount > 0) {
        printf("Unprocessed transactions:\n");
        for (int i = 0; i < tobeprocessedCount; i++) {
            printf("%d AED\n", tobeprocessed[i]);
        }
    } else {
        printf("No unprocessed transactions.\n");
    }
}

int main() {
    
    int transactions[] = {100, -1250, -4500, -1100, -510, -100, 3400};
    int numTransactions = sizeof(transactions) / sizeof(transactions[0]);

    processTransactions(transactions, numTransactions);

    return 0;
}
