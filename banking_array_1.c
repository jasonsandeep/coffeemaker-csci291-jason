#include <stdio.h>

#define INITIAL_BALANCE 1000
#define MAX_TRANSACTIONS 100

// Function to process the transactions
void processTransactions(int transactions[], int numTransactions) {
    int balance = INITIAL_BALANCE;
    int tobeProcessed[MAX_TRANSACTIONS];
    int tobeProcessedCount = 0;

    printf("Initial balance: %d AED\n", balance);

    for (int i = 0; i < numTransactions; i++) {
        int transaction = transactions[i];

        // Check if the transaction is a withdrawal and exceeds the current balance
        if (transaction < 0 && balance + transaction < 0) {
            printf("Transaction %d AED is invalid: Insufficient funds. Transaction skipped.\n", transaction);
            tobeProcessed[tobeProcessedCount++] = transaction;  // Store invalid transaction
        }
        // Process the transaction if it's valid
        else {
            balance += transaction;
            printf("Transaction %d AED processed. New balance: %d AED\n", transaction, balance);

            if (balance <= 0) {
                printf("Balance has reached 0 AED. Stopping further transactions.\n");
                tobeProcessed[tobeProcessedCount++] = transaction;  // Store the last transaction
                break;  // Stop further processing
            }
        }
    }

    // Final balance and unprocessed transactions
    printf("\nFinal balance: %d AED\n", balance);

    // Display unprocessed transactions (those stored in tobeProcessed array)
    if (tobeProcessedCount > 0) {
        printf("Unprocessed transactions:\n");
        for (int i = 0; i < tobeProcessedCount; i++) {
            printf("%d AED\n", tobeProcessed[i]);
        }
    } else {
        printf("No unprocessed transactions.\n");
    }
}

int main() {
    // Sample transactions: Positive values are deposits, negative values are withdrawals
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int numTransactions = sizeof(transactions) / sizeof(transactions[0]);

    processTransactions(transactions, numTransactions);

    return 0;
}

