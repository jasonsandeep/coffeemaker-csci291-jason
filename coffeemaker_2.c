#include <stdio.h>
void user();
void admin();
 int main()
 {
int option;
int a;
int b;
int c;
int password;
float payment;
float price=0.0;
float totalpayment=0.0;
int adminpass=123;
 printf("Coffee Maker\n");
 printf("/------------------------------------------/\n");
 printf("1.Order a Coffee \n ");
 printf("2.Admin mode \n ");
 printf("3.Exit \n ");
 printf("Enter option 1-3:");
 
 scanf("%d",&option);
 if (option==1)
{
	int coffee;
	while(1){
printf("/------------------------------------------/\n");
printf("Choose coffee:\n");
printf("1.Espresso - 3.5 AED \n ");
printf("2.Cappuccino - 4.5 AED\n ");
printf("3.Mocha - 5.5 AED \n ");
printf("0.Exit\n ");
printf("Enter option 0-3:");
 
  scanf("%d", &coffee);
            if (coffee == 1) {
                price = 3.5;
                printf("You chose Espresso - 3.5AED\n", price);
            } else if (coffee == 2) {
                price = 4.5;
                printf("You chose Cappuccino - 4.5AED\n", price);
            } else if (coffee == 3) {
                price = 5.5;
                printf("You chose Mocha - 5.5AED\n", price);
            } else if (coffee == 0) {
                break;
            } else {
                printf("Invalid Option. Try Again.\n");
                continue;
            }
 while (totalpayment < price) {
  printf("Insert %.2f AED in coins (1.0 or 0.5 AED): ", price);
  scanf("%f", &payment);
  if (payment == 1.0 || payment == 0.5) {
     totalpayment += payment;
       printf("Total paid: %.2f AED\n", totalpayment);
	   } else {
	   printf("Invalid coin. Please insert 1.0 or 0.5 AED.\n");
	   }
if (totalpayment >= price) 
{printf("Enjoy your Coffee!\n");
return 0; }
}
}
}
else if (option==2)
{
	int option;
	while(1){
	
	printf("Enter admin password:");
	scanf("%d",&password);
	if (password==adminpass){
	printf("Acess Granted\n");
printf("1.Display the quantity of each ingredient in the machine and the Total sale amount \n ");
 printf("2.Replenish ingredients in the machine \n ");
 printf("Change coffee price \n ");
 printf("Exit the Admin Mode function \n ");
 printf("Enter option 0-3:");
 scanf("%d",&option);
 
  if (option == 1) {
  printf("total sale");
}
else if (option==2)
{
printf("replenish ingreditents");	
}
 
 
 
 
 
 
 
 
 
 
break;
	}

	else {
	printf("Incorrect Password. Try Again.\n");
	}
}
}






















else if (option==3)
{
	printf("Exiting...");
	return 0;
}

else
{
	printf("Invalid Option. Try Again.\n");
}
}

