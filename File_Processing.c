#include <stdio.h>
#include <stdlib.h>

int is_float(const char*str) {
    char*endptr;
    strtod(str, &endptr);
    return*endptr == '\0';
}

int main() {
    FILE *inputFile = fopen("data.txt", "r");
    if (!inputFile) return 1;

    FILE *outputFile = fopen("valid_data.txt", "w");
    if (!outputFile) {
        fclose(inputFile);
        return 1;
    }

    char buffer[50];
    int invalidCount = 0;

    while (fscanf(inputFile, "%s", buffer) != EOF) {
        if (is_float(buffer)) {
            fprintf(outputFile, "%s\n", buffer);
        } else {
            invalidCount++;
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Number of invalid values: %d\n", invalidCount);
    printf("Valid data saved to valid_data.txt\n");

    return 0;
}
