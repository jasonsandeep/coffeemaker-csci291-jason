#include <stdio.h>
#include <stdlib.h>

// Define constants for admin password and ingredient thresholds
#define adminpass 123
#define beans 8
#define syrup 30
#define water 30
#define water2 39
#define milk 70
#define milk2 160

// Functions
void user();
void admin();

int main() {
    int option; // Variable to store user's menu choice
    float payment; // Variable to store the payment made by the user
    float price = 0.0; // Variable to store the price of the chosen coffee
    float totalpayment = 0.0; // Variable to accumulate total payment
    double espresso_price = 3.5; // Price of espresso
    double cappuccino_price = 4.5; // Price of cappuccino
    double mocha_price = 5.5; // Price of mocha
    
    // Randomly generate ingredient availability
    int beans_availability = rand() % 100 + 50;
    int water_availability = rand() % 100 + 200;
    int milk_availability = rand() % 200 + 1000;
    int syrup_availability = rand() % 100 + 50;
    double total_amount = 0.0; // Variable to store total sales amount

    while (1) { // Infinite loop for the main menu
        printf("Coffee Maker\n");
        printf("/------------------------------------------/\n");
        printf("1. Order a Coffee\n");
        printf("2. Admin mode\n");
        printf("3. Exit\n");
        printf("Enter option 1-3: ");
        scanf("%d", &option);

        if (option == 1) { // User chooses to order coffee
            int coffee; // Variable to store coffee type choice
            while (1) { // Infinite loop for coffee selection
                printf("/------------------------------------------/\n");
                printf("Choose coffee:\n");
                printf("1. Espresso - %.2f AED\n", espresso_price);
                printf("2. Cappuccino - %.2f AED\n", cappuccino_price);
                printf("3. Mocha - %.2f AED\n", mocha_price);
                printf("0. Exit\n");
                printf("Enter option 0-3: ");
                scanf("%d", &coffee);

                // Check for coffee availability based on user selection
                if (coffee == 1) {
                    price = espresso_price; // Set price for espresso
                    if (beans_availability < beans || water_availability < water) {
                        printf("Unavailable due to insufficient ingredients.\n");
                        continue; // Re-prompt for coffee selection
                    }
                    printf("You chose Espresso - %.2f AED\n", price);
                    printf("/------------------------------------------/\n");
                } else if (coffee == 2) {
                    price = cappuccino_price; // Set price for cappuccino
                    if (beans_availability < beans || water_availability < water || milk_availability < milk) {
                        printf("Unavailable due to insufficient ingredients.\n");
                        continue; // Re-prompt for coffee selection
                    }
                    printf("You chose Cappuccino - %.2f AED\n", price);
                    printf("/------------------------------------------/\n");
                } else if (coffee == 3) {
                    price = mocha_price; // Set price for mocha
                    if (beans_availability < beans || water_availability < water2 || milk_availability < milk2 || syrup_availability < syrup) {
                        printf("Unavailable due to insufficient ingredients.\n");
                        continue; // Re-prompt for coffee selection
                    }
                    printf("You chose Mocha - %.2f AED\n", price);
                    printf("/------------------------------------------/\n");
                } else if (coffee == 0) {
                    break; // Exit coffee selection loop
                } else {
                    printf("Invalid Option. Try Again.\n");
                    continue; // Re-prompt for coffee selection
                }

                totalpayment = 0.0; // Reset total payment for the current order
                while (totalpayment < price) { // Loop until full payment is made
                    printf("Insert %.2f AED in coins (1.0 or 0.5 AED): ", price);
                    scanf("%f", &payment); // Get user payment
                    if (payment == 1.0 || payment == 0.5) {
                        totalpayment += payment; // Add payment to total
                        printf("Total paid: %.2f AED\n", totalpayment);
                    } else {
                        printf("Invalid coin. Please insert 1.0 or 0.5 AED.\n");
                    }
                }

                // If payment is complete, process the order
                if (totalpayment >= price) {
                    printf("Enjoy your Coffee!\n");
                    total_amount += price; // Update total sales amount
                    beans_availability -= beans; // Deduct used ingredients
                    
                    // Deduct additional ingredients based on coffee type
                    if (coffee == 2) milk_availability -= 70;
                    if (coffee == 3) {
                        milk_availability -= 160;
                        syrup_availability -= 30;
                    }
                    // Check for low ingredient warnings
                    if (beans_availability <= 10) {
                        printf("Warning: Low beans!\n");
                    }
                    if (water_availability <= 50) {
                        printf("Warning: Low water!\n");
                    }
                    if (milk_availability <= 100) {
                        printf("Warning: Low milk!\n");
                    }
                    if (syrup_availability <= 20) {
                        printf("Warning: Low syrup!\n");
                    }
                    break; // Exit coffee selection loop
                }
            }
        } else if (option == 2) { // User chooses admin mode
            int password; // Variable to store admin password input
            printf("Enter admin password: ");
            scanf("%d", &password); // Get admin password
            if (password == adminpass) { // Check password
                printf("Access Granted\n");
                printf("/------------------------------------------/\n");
                int admin_option; // Variable to store admin option
                while (1) { // Infinite loop for admin menu
                    printf("1. Display ingredients and total sale amount\n");
                    printf("2. Replenish ingredients\n");
                    printf("3. Change coffee price\n");
                    printf("4. Reset Total Sale\n");
                    printf("0. Exit Admin Mode\n");
                    printf("Enter option 0-4: ");
                    scanf("%d", &admin_option); // Get admin option

                    if (admin_option == 1) { // Display ingredients and sales
                        printf("/------------------------------------------/\n");
                        printf("Ingredients:\n");
                        printf("Beans: %d\n", beans_availability);
                        printf("Water: %d\n", water_availability);
                        printf("Milk: %d\n", milk_availability);
                        printf("Chocolate Syrup: %d\n", syrup_availability);
                        printf("/------------------------------------------/\n");
                        printf("Total sale amount: %.2f\n", total_amount);
                        printf("/------------------------------------------/\n");
                    } else if (admin_option == 2) { // Replenish ingredients
                        beans_availability = rand() % 100 + 50;
                        water_availability = rand() % 100 + 200;
                        milk_availability = rand() % 200 + 1000;
                        syrup_availability = rand() % 100 + 50;                       
                        printf("Ingredients replenished.\n");
                        printf("/------------------------------------------/\n");
                    } else if (admin_option == 3) { // Change coffee prices
                        printf("/------------------------------------------/\n");
                        printf("Current prices:\n");
                        printf("Espresso: %.2f\n", espresso_price);
                        printf("Cappuccino: %.2f\n", cappuccino_price);
                        printf("Mocha: %.2f\n", mocha_price);
                        int coffee_choice; // Variable to store coffee price choice
                        double new_price; // Variable to store new price
                        printf("/------------------------------------------/\n");
                        printf("Which coffee price would you like to update? (1/2/3): ");
                        scanf("%d", &coffee_choice); // Get coffee price choice
                        if (coffee_choice == 1) {
                            printf("Enter new price for Espresso: ");
                            scanf("%lf", &new_price); // Get new espresso price
                            espresso_price = new_price; // Update espresso price
                        } else if (coffee_choice == 2) {
                            printf("Enter new price for Cappuccino: ");
                            scanf("%lf", &new_price); // Get new cappuccino price
                            cappuccino_price = new_price; // Update cappuccino price
                        } else if (coffee_choice == 3) {
                            printf("Enter new price for Mocha: ");
                            scanf("%lf", &new_price); // Get new mocha price
                            mocha_price = new_price; // Update mocha price
                        } else {
                            printf("Invalid choice.\n");
                        }
                    } else if (admin_option == 4) { // Reset total sales option
                        char option; // Variable to store user confirmation
                        printf("Would you like to set the total sale to 0.0? (Y/N): ");
                        scanf(" %c", &option); // Get user confirmation
                        if (option == 'Y' || option == 'y') {
                            total_amount = 0.0; // Reset total sales
                            printf("Total sale value changed to 0.0\n");
                        } else if (option == 'N' || option == 'n') {
                            printf("Total sale value not changed\n");
                        } else {
                            printf("Invalid Option\n");
                        }
                    } else if (admin_option == 0) {
                        break; // Exit admin menu
                    } else {
                        printf("Invalid option. Try again.\n");
                    }
                }
            } else {
                printf("Incorrect Password. Try Again.\n"); // Invalid password message
            }
        } else if (option == 3) { // Exit option
            printf("Exiting...\n");
            return 0; // Exit program
        } else {
            printf("Invalid Option. Try Again.\n"); // Invalid option message
        }
    }
}
