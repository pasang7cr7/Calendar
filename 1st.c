#include<stdio.h>
#include<conio.h>
int checklp(int year);
int calcTotalDays(int year);
 int main()
 {
    int monthDays[]= {0, 31,28,31,30,31,30,31,31,30,31,30,31};
    int totaldays;
    int month, year,week;
    char *weekDays[]={"sun","mon","tue","wed","thu","fri","sat"};
    printf("Enter year and month: ");
    scanf("%d%d",&year,&month);
    totaldays= calcTotalDays(year);
    int i=1;
    while( i<month)
    {
        totaldays= totaldays + monthDays[i];
        if(i==2)
        {
            totaldays= totaldays+checklp(year);
        }
        i++;
    }
    printf("total dsys ios %d \n", totaldays);
    week= totaldays%7;
    printf("the last day of previous month was %s \n", weekDays[week]);
    week++;
    printf("the first day of this month was %s", weekDays[week]);
     return 0;
 }

 int checklp(year)
 {
     if(year%400==0)
        return 1;
     else if(year%4==0 && year %100!=0)
        return 1;
     else
        return 0;
 }
 int calcTotalDays(year)
 {
     int totaldays=0;
     totaldays=365*(year-1);
     for(int i=1; i<year;i++)
     {
         totaldays= totaldays+ checklp(i);
     }
     return totaldays;
 }
