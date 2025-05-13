// try to make claendar in funciton


#include<stdio.h>
#include<conio.h>
#include<string.h>
int checklp(int year);
int calcTotalDays(int year);
void printCalendar(int weekDays, int monthDays);
void main2();
void addEvent();
void viewEvent();
void deleteEvent();


struct event {
    int year, month, day;
    char note[100];

};

 int main()
 {
 	printf("----------------------------------------\n");
 	printf("       Calendar Management System       \n");
 	printf("----------------------------------------\n");
    int choice;
    struct event e[100];
    int eventcount = 0;
    // printf("etner your choice: ");
     //scanf("%d", &choice);
    while(1)
    {
        
     printf("\n 1.View calendar. \n 2.Add Event \n 3.View Event \n 4.Delete event \n 5.Exit ");
     printf(" \n");
     printf("\n  Enter your choice: ");
     scanf("%d", &choice);



        switch(choice)
        {
        case 1:
             main2();
            break;
        case 2:
            addEvent();
            break;
        case 3:
            viewEvent();
            break;
        case 4:
            deleteEvent();
            break;
        case 5:
            return 1;
        }
    }
     return 0;
 }
 void main2()
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
    printf("total days is %d \n", totaldays);
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

 void addEvent()
 {
    FILE* ptr;
    int year,month,day;
    char notes[100];
    ptr = fopen("event.txt", "a");

        printf("enter the date (yy/mm/dd): ");
        scanf("%d%d%d", &year,&month, &day);
        getchar();

        printf("Enter your notes: ");
        fgets(notes, sizeof(notes), stdin);

        size_t len = strlen(notes);
    if (len > 0 && notes[len - 1] == '\n') {
        notes[len - 1] = '\0';
    }

    fprintf(ptr, " %d %d %d:  %s\n " , year, month , day , notes);
        fclose(ptr);
        printf("Event added Successfully\n");

 } 
 
 /*void viewEvent()
 {
 	FILE* src = fopen("event.txt", "r");
 	int year, month, day;
 	
 	char notes[100];
 	char ch;
 	while((ch=fgetc(src))!=EOF)
 	{
 		fscanf(src, "%d %d %d %s", &year, &month, &day, &notes);
 		printf("%d %d %d %s", year, month , day ,notes );
	 }
	 fclose(src);
 	
 	
 }
 
 */
 
 void viewEvent()
 {
 		FILE *ptr =fopen("event.txt","r");
	char notes[200];
	int year, month, day;
	char line[200];
    printf("\n%-12s %-10s\n", "Date", "Note");
    printf("---------------------------\n");

    while (fgets(line, sizeof(line), ptr) != NULL)
    {
        if (sscanf(line, "%d %d %d: %[^\n]", &year, &month, &day, notes) == 4)
        {
            printf("%04d-%02d-%02d  %s\n", year, month, day, notes);
        }
    }
	printf("\n");
	fclose(ptr);
 }
 
 void deleteEvent()
 {
 	FILE* src = fopen("event.txt", "r");
	FILE* temp = fopen("temp.txt", "w"); 
	
	char notes[200], line[200];	
	int year, month, day;
	
	int dyear, dmonth, dday;
 	printf("enter event to delete (yy/mm/dd): ");
 	scanf("%d %d %d", &dyear, &dmonth, &dday);
 	
 	int deleted = 0;
 	
 	while(fgets(line, sizeof(line), src)!=NULL)
 	{
 		if(sscanf(line,"%d %d %d %[^\n]", &year, &month, &day, &notes)==4)
 		{
 			if(year==dyear && month == dmonth && day == dday)
			 {
			 	deleted =1;
			 	continue;
				 }	
		 }
		 fputs(line, temp);
	 }
	 fclose(src);
	 fclose(temp);
	 
	 remove("event.txt");
	 rename("temp.txt", "event.txt");
	 
	 if(deleted)
	 {
	 	printf("Successfully Deleted ");
	 	
	 }
	 else 
	 {
	 	printf("The event not found");
	 }
	 
 }
 
 
 
 
 
