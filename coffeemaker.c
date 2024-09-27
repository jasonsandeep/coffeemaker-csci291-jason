#include <stdio.h>
void user();
void admin();
 int main()
 {
int option;
 printf("1.Order a Coffee \n ");
 printf("2.Admin mode \n ");
 printf("3.Exit \n ");
 printf("Enter option 1-3:");
 
 scanf("%d",&option);
 if (option==1)
{
printf("Choose coffee:");
return 0;
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

 
