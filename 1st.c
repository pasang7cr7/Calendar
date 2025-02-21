#include<stdio.h>
#include<conio.h>
int checkLeap(   );
int calculateTotalDays(int, int);
 int main()
 {
     printf("is leap year: %d", checkLeap());
     return 0;
 }

int checkLeap()
 {
    int year;
    printf("enter any year: ");
    scanf("%d",&year);
    if(year%400==0 || (year%4==0 && year%100!=0))
    {
return 1;
    }
    else
    {
        return 0;
    }

 }

 int calculateTotalDays(int month, int year)
 {
     int totalDays;
     totalDays=365*year;
     return totalDays;
 }
