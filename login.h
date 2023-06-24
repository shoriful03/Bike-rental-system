#include<stdio.h>
void login()
{
	int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char user[10]="username";
    char pass[10]="password";
    do
{

    printf("\n  <<<<<<<<<<<<<<<<<<<<<<<<<  LOGIN PANEL  >>>>>>>>>>>>>>>>>>>>>>>>>>  ");
    printf(" \n                       ENTER USERNAME:-");
	scanf("%s", &uname);
	printf(" \n                       ENTER PASSWORD:-");
	while(i<10)
	{
	    pword[i]=getch();
	    c=pword[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';
	//char code=pword;
	i=0;
	//scanf("%s",&pword);
		if(strcmp(uname,"username")==0 && strcmp(pword,"password")==0)
	{
	printf("  \n\n\n        YOU ARE LOGGED IN. WELCOME TO OUR BIKE RENTING SYSTEM !");
	printf("\n\n\n\t\t\t\tPress any key to continue...");
	getch();//holds the screen
	break;
	}
	else
	{
		printf("\n        SORRY !!!!  LOGIN IS UNSUCESSFUL");
		a++;

		getch();//holds the screen

	}
}
	while(a<=2);
	if (a>2)
	{
		printf("\nSorry you have entered the wrong username and password for four times!!!");

		getch();

		}
		system("cls");
}

