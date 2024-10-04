#include <stdio.h>
void user();
void admin();
 int main()
 {
int option;
int a;
int b;
int c;
float payment;
float price=0.0;

 printf("1.Order a Coffee \n ");
 printf("2.Admin mode \n ");
 printf("3.Exit \n ");
 printf("Enter option 1-3:");
 
 scanf("%d",&option);
 if (option==1)
{
	int coffee;
	while(1){
printf("/-----------------------------------------------------/\n");
printf("Choose coffee:\n");
printf("1.Espresso - 3.5 AED \n ");
printf("2.Cappuccino - 4.5 AED\n ");
printf("3.Mocha - 5.5 AED \n ");
printf("0.Exit\n ");
printf("Enter option 0-3:");
 
scanf("%d",&coffee);
if (coffee==1){
	price = 3.5;
	printf("You chose Espresso - 3.5 AED\n");
	printf("Insert 3.5 AED in exact change:",price);
	scanf("%f",&payment);
	
	if (payment==price)
	{
	printf("Enjoy your Coffee!");
	break;
	}
	
	
else if (coffee==2)
{
	
	printf("You chose Cappuccino - 4.5 AED");
}
else if (coffee==3)
{
	printf("You chose Mocha - 5.5 AED");	
}
else if (coffee==0)
{
	break;
}


else
{
	printf("Invalid Option. Try Again.\n");
	continue;
}

	



}
}
}
else if (option==2)
{
	printf("Enter admin password:");
	return 0;
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


 
