#include<stdio.h>
#include<conio.h>
int checklp(int year);
int calcTotalDays(int year);
void printCalendar(int weekDays, int monthDays);
 int main()
 {
    int monthDays[]= {0, 31,28,31,30,31,30,31,31,30,31,30,31};
    int totaldays;
    int month, year,weekday;
    char *weekDays[]={"sun","mon","tue","wed","thu","fri","sat"};
    printf("Enter year and month: ");
    scanf("%d%d",&year,&month);
    totaldays= calcTotalDays(year);
    int i=1;
    while( i<month)
    {
        totaldays= totaldays + monthDays[i];
       /* if(i==2)
        {
            totaldays= totaldays+checklp(year);
            monthDays[2]= monthDays[2]+1;

        } */
        i++;
    }
    if(month>2 && checklp(year))
    {

        totaldays+= 1;
    }
    printf("total dsys ios %d \n", totaldays);
    weekday= totaldays%7;
    printf("the last day of previous month was %s \n", weekDays[weekday]);
    weekday++;
    printf("the first day of this month was %s\n", weekDays[weekday]);
    int daysInMonth = monthDays[month];
    if(month==2 && checklp(year))
    {
        daysInMonth+=1;
         printf("%d", daysInMonth);
    }

    printf("\n\n");



    printCalendar(weekday, daysInMonth);
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
 	int i;
     int totaldays=0;
     totaldays=365*(year-1);
     for( i=1; i<year;i++)
     {
         totaldays= totaldays+ checklp(i);
     }
     return totaldays;
 }
 void printCalendar(int weekday, int monthDays)
 {
    int i=1;
     char *weekDays[] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
     while(i<=7)
     {

         printf("%s\t", weekDays[i-1]);
         i++;
     }
     printf("\n\n");
         i=1;
     while(i<=weekday)
     {
       printf(" \t");
       i++;
    }
     i=1;
     while(i<=monthDays)
     {
        printf("%d\t",i);
        i++;
        weekday++;
        if(weekday%7==0)
            printf("\n");

     }
 }
