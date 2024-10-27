
#include <stdio.h>
#include <stdlib.h>
#define adminpass 123
#define beans 8
#define syrup 30
#define water 30
#define water2 39
#define milk 70
#define milk2 160
void user();
void admin();

int main() {
    int option;
    float payment;
    float price = 0.0;
    float totalpayment = 0.0;
    double espresso_price = 3.5;
    double cappuccino_price = 4.5;
    double mocha_price = 5.5;
    
    int beans_availability = rand()% 100+50;
    int water_availability = rand()%100+200;
    int milk_availability = rand()% 200+1000;
    int syrup_availability = rand()% 100+50;
    double total_amount = 0.0;

    while (1) {
        printf("Coffee Maker\n");
        printf("/------------------------------------------/\n");
        printf("1. Order a Coffee\n");
        printf("2. Admin mode\n");
        printf("3. Exit\n");
        printf("Enter option 1-3: ");
        scanf("%d", &option);

        if (option == 1) {
            int coffee;
            while (1) {
                printf("/------------------------------------------/\n");
                printf("Choose coffee:\n");
                printf("1. Espresso - %.2f AED\n", espresso_price);
                printf("2. Cappuccino - %.2f AED\n", cappuccino_price);
                printf("3. Mocha - %.2f AED\n", mocha_price);
                printf("0. Exit\n");
                printf("Enter option 0-3: ");
                scanf("%d", &coffee);

                if (coffee == 1) {
                    price = espresso_price;
                    if (beans_availability < 8 || water_availability < 30) {
                        printf("Unavailable due to insufficient ingredients.\n");
                        continue;
                    }
                    printf("You chose Espresso - %.2f AED\n", price);
                    printf("/------------------------------------------/\n");
                } else if (coffee == 2) {
                    price = cappuccino_price;
                    if (beans_availability < 8 || water_availability < 30 || milk_availability < 70) {
                        printf("Unavailable due to insufficient ingredients.\n");
                        continue;
                    }
                    printf("You chose Cappuccino - %.2f AED\n", price);
                    printf("/------------------------------------------/\n");
                } else if (coffee == 3) {
                    price = mocha_price;
                    if (beans_availability < 8 || water_availability < 39 || milk_availability < 160 || syrup_availability < 30) {
                        printf("Unavailable due to insufficient ingredients.\n");
                        continue;
                    }
                    printf("You chose Mocha - %.2f AED\n", price);
                    printf("/------------------------------------------/\n");
                } else if (coffee == 0) {
                    break;
                } else {
                    printf("Invalid Option. Try Again.\n");
                    continue;
                }

                totalpayment = 0.0;
                while (totalpayment < price) {
                    printf("Insert %.2f AED in coins (1.0 or 0.5 AED): ", price);
                    scanf("%f", &payment);
                    if (payment == 1.0 || payment == 0.5) {
                        totalpayment += payment;
                        printf("Total paid: %.2f AED\n", totalpayment);
                    } else {
                        printf("Invalid coin. Please insert 1.0 or 0.5 AED.\n");
                    }
                }

                if (totalpayment >= price) {
                    printf("Enjoy your Coffee!\n");
                    total_amount += price;
                    beans_availability -= 8;
                    
                    if (coffee == 2) milk_availability -= 70;
                    if (coffee == 3) {
                        milk_availability -= 160;
                        syrup_availability -= 30;
                    }
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
                    break;
                }
            }
        } else if (option == 2) {
            int password;
             {
                printf("Enter admin password: ");
                scanf("%d", &password);
                if (password == adminpass) {
                    printf("Access Granted\n");
                    printf("/------------------------------------------/\n");
                    int admin_option;
                    while (1) {
                        printf("1. Display ingredients and total sale amount\n");
                        printf("2. Replenish ingredients and Reset total sale number\n");
                        printf("3. Change coffee price\n");
                        printf("4. Reset Total Sale\n");
                        printf("0. Exit Admin Mode\n");
                        printf("Enter option 0-4: ");
                        scanf("%d", &admin_option);

                        if (admin_option == 1) {
                        	printf("/------------------------------------------/\n");
                            printf("Ingredients:\n");
                            printf("Beans: %d\n", beans_availability);
                            printf("Water: %d\n", water_availability);
                            printf("Milk: %d\n", milk_availability);
                            printf("Chocolate Syrup: %d\n", syrup_availability);
                            printf("/------------------------------------------/\n");
                            printf("Total sale amount: %.2f\n", total_amount);
                            printf("/------------------------------------------/\n");
                        } else if (admin_option == 2) {
                            beans_availability = rand()% 100+50;
							water_availability = rand()%100+200;
							milk_availability = rand()% 200+1000;
							syrup_availability = rand()% 100+50;
                            total_amount = 0;
                            printf("Ingredients replenished.\n");
                            printf("/------------------------------------------/\n");
                        } else if (admin_option == 3) {
                        	printf("/------------------------------------------/\n");
                            printf("Current prices:\n");
                            printf("Espresso: %.2f\n", espresso_price);
                            printf("Cappuccino: %.2f\n", cappuccino_price);
                            printf("Mocha: %.2f\n", mocha_price);
                            int coffee_choice;
                            double new_price;
                            printf("/------------------------------------------/\n");
                            printf("Which coffee price would you like to update? (1/2/3): ");
                            scanf("%d", &coffee_choice);
                            if (coffee_choice == 1) {
                                printf("Enter new price for Espresso: ");
                                scanf("%lf", &new_price);
                                espresso_price = new_price;
                            } else if (coffee_choice == 2) {
                                printf("Enter new price for Cappuccino: ");
                                scanf("%lf", &new_price);
                                cappuccino_price = new_price;
                            } else if (coffee_choice == 3) {
                                printf("Enter new price for Mocha: ");
                                scanf("%lf", &new_price);
                                mocha_price = new_price;
                            } else {
                                printf("Invalid choice.\n");
                            }
                        }
                           else if (admin_option == 4) {
						   char option;
						   printf("Would you like to set the total sale to 0.0? (Y/N): ");
						   scanf(" %c", &option);
						   if (option == 'Y' || option == 'y') {
						   total_amount = 0.0;
						   printf("Total sale value changed to 0.0\n");
						   } else if (option == 'N' || option == 'n') {
						   printf("Total sale value not changed\n");
						   } else {
						   printf("Invalid Option\n");
						   }
						   }
                         else if (admin_option == 0) {
                            break;
                        } else {
                            printf("Invalid option. Try again.\n");
                        }
                    }
                } else {
                    printf("Incorrect Password. Try Again.\n");
                }
            }
        } else if (option == 3) {
            printf("Exiting...\n");
            return 0;
        } else {
            printf("Invalid Option. Try Again.\n");
        }
    }
}
