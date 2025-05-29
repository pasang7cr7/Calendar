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
void todo();

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

     printf("\n\n 1.View calendar. \n 2.Add Event \n 3.View Event \n 4.Delete event\n 5.To-do list \n 6.Exit ");
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
        	todo();
        	break;
        case 6:
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
    printf(" Enter year and month: ");
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
 void addtodo();
 void viewtodo();
 void marktodo();
 void view_completedtodo();


 void todo()
 {
 	int choice;
 	printf("------------------------------\n");
 	printf("          To-DO list          \n");
 	printf("------------------------------\n");



        while(1)
        {
        	printf("\n");
        	printf("1. Add To-Do\n");
        	printf("2. View To-Do List\n");
        	printf("3. Mark Task as Completed\n");
        	printf("4. View Completed Tasks\n");
        	printf("5. Exit to Main Menu\n");
        	printf("---------------------------------------\n");
        	printf("\nEnter your choice: ");
       		scanf("%d", &choice);
       		printf("\n");
        	getchar(); // Clear buffer
        	  switch(choice)
        	{
        		case 1:
        			addtodo();
        			break;
	        	case 2:
	        		viewtodo();
	        		break;
	        	case 3:
	        		marktodo();
	        		break;
	        	case 4:
	        	    view_completedtodo();
	        		break;
	         	case 5:
	                printf("Exiting program.\n");
	                return;

	        	default:
	        		printf("Invalid Choice");
			}
		}



 }

 void addtodo()
 {
 	FILE* ptr ;
	ptr = fopen("todo.txt", "a");
	char task[200];


	printf("Enter task to do: \n");
	fgets(task, sizeof(task), stdin);
        size_t len = strlen(task);
    if (len > 0 && task[len - 1] == '\n') {
        task[len - 1] = '\0';
    }
        if (strlen(task) == 0) {
        printf("Task cannot be empty.\n");
        fclose(ptr);
        return;
    }


    fprintf(ptr, "%s\n",task);
        fclose(ptr);
        printf("\nTask added Successfully!\n");
        printf("--------------------------------------\n");



 }

 void viewtodo()
{
		FILE *fp = fopen("todo.txt", "r");
    if (!fp) {
        printf("No tasks found.\n");
        return;
    }

    char line[200];
    int count = 1;
    printf("\n--- To-Do List ---\n");
    printf("\n");
    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';
        printf("%d. %s\n", count++, line);
    }

    if (count == 1) {
        printf("No tasks found.\n");
    }
    printf("--------------------------\n");

    fclose(fp);
}

void marktodo()
{
    FILE* src = fopen("todo.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    FILE* completed = fopen("complete.txt", "a");

   if(!src || !temp || !completed)
  {
      printf("Error opening files!\n\n");
        return;
    }

    char task[200][200];
    int count = 0;

 while (fgets(task[count], sizeof(task[count]), src))
    {
        size_t len = strlen(task[count]);
         if (len > 0 && task[count][len - 1] == '\n')
        {
         task[count][len-1] = '\0';
        }
        count++;
    }

    if(count == 0)
    {
        printf("No tasks found!\n\n");
        fclose(src);
        fclose(temp);
        fclose(completed);
        return;
    }
    int i;

    printf("--To-Do List--\n");
    for(i=0;i<count;i++)
    {
        printf("%d. %s\n", i+1, task[i]);
    }


    int choice;
    printf("Enter task number that is completed\n");
    scanf("%d", &choice);
    getchar();

    if(choice<1 || choice > count)
    {
        printf("Invalid choice. \n");
        fclose(src);
        fclose(temp);
        fclose(completed);
        return;
    }

    for(i=0;i<count;i++)
    {
        if(i == choice - 1)
        {
            fprintf(completed, "%s\n", task[i]);
        }
        else
        {
            fprintf(temp, "%s\n", task[i]);
        }
    }
     fclose(src);
    fclose(temp);
    fclose(completed);

    remove("todo.txt");
    rename("temp.txt", "todo.txt");

    printf("Task marked as completed.\n");

}

void view_completedtodo()
{
    FILE* src= fopen("complete.txt", "r");

   if(!src)
  {
      printf("Error opening files!\n\n");
        return;
    }

    char task[200][200];
    int count = 0;
    int i;

    while(fgets(task[count], sizeof(task[count]), src))
    {
        size_t len = strlen(task[count]);
        if(len > 0 && task[count][len-1]== '\n')
        {
            task[count][len-1] = '\0';
        }
        count++;
    }
    if(count == 0)
    {
        printf("no completed task\n");
    }
    else
    {
            printf("--Completed To-Do List--\n\n");
    for(i=0;i<count;i++)
    {
        printf("%d. %s\n", i+1, task[i]);
    }

    }
    printf("\n\n");
    printf("---------------------------------");


    fclose(src);

}






