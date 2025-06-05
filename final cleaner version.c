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

int main() {
    printf("----------------------------------------\n");
    printf("       Calendar Management System       \n");
    printf("----------------------------------------\n");
    int choice;
    struct event e[100];
    int eventcount = 0;

    while (1) {
        printf("1. View calendar.\n");
        printf("2. Add Event\n");
        printf("3. View Event\n");
        printf("4. Delete Event\n");
        printf("5. To-do list\n");
        printf("6. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
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
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void main2() {
    int monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int totaldays;
    int month, year, weekday;
    char *weekDays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    printf("\nEnter year and month: ");

    scanf("%d%d", &year, &month);
    printf("\n");

    totaldays = calcTotalDays(year);

    int i = 1;
    while (i < month) {
        totaldays = totaldays + monthDays[i];
        i++;
    }

    if (month > 2 && checklp(year)) {
        totaldays += 1;
    }

    //printf("Total days: %d\n", totaldays);
    weekday = totaldays % 7;
  //  printf("The last day of the previous month was: %s\n", weekDays[weekday]);
    weekday++;
  //  printf("The first day of this month was: %s\n", weekDays[weekday]);

    int daysInMonth = monthDays[month];
    if (month == 2 && checklp(year)) {
        daysInMonth += 1;
      //  printf("February has %d days in %d\n", daysInMonth, year);
    }

    printCalendar(weekday, daysInMonth);
}

int checklp(int year) {
    if (year % 400 == 0)
        return 1;
    else if (year % 4 == 0 && year % 100 != 0)
        return 1;
    else
        return 0;
}

int calcTotalDays(int year) {
    int i;
    int totaldays = 0;
    totaldays = 365 * (year - 1);
    for (i = 1; i < year; i++) {
        totaldays = totaldays + checklp(i);
    }
    return totaldays;
}

void printCalendar(int weekday, int monthDays) {
    int i = 1;
    char *weekDays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    printf("----------------------------------------\n");

    // Print header (weekdays)
    for (i = 1; i <= 7; i++) {
        printf("%-6s", weekDays[i - 1]);
    }
    printf("\n");

    i = 1;
    while (i <= weekday) {
        printf("      ");
        i++;
    }

    i = 1;
    while (i <= monthDays) {
        printf("%-6d", i);
        i++;
        weekday++;
        if (weekday % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    printf("----------------------------------------\n");
    //printf("\n");
}

void addEvent() {
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
        printf("\nEvent added Successfully\n");
        printf("----------------------------------------\n");

}

void viewEvent() {
    FILE *ptr = fopen("event.txt", "r");
    char notes[200];
    int year, month, day;
    char line[200];
    int eventFound = 0;  // Flag to track if events are found

    printf("\n%-12s %-10s\n", "Date", "Note");
    printf("---------------------------\n");

    while (fgets(line, sizeof(line), ptr) != NULL) {
        if (sscanf(line, "%d %d %d: %[^\n]", &year, &month, &day, notes) == 4) {
            printf("%04d-%02d-%02d  %s\n", year, month, day, notes);
            eventFound = 1;  // Set flag when an event is found
        }
    }

    if (!eventFound) {  // If no event was found, print the message
        printf("No event found.\n");
    }

    printf("----------------------------------------\n");
    printf("\n");
    fclose(ptr);
}


void deleteEvent() {
    FILE* src = fopen("event.txt", "r");
    FILE* temp = fopen("temp.txt", "w");


      char notes1[200];
    int year1, month1, day1;
    char line1[200];
    int eventFound = 0;  

    printf("\n%-12s %-10s\n", "Date", "Note");
    printf("---------------------------\n");

    while (fgets(line1, sizeof(line1), src) != NULL) {
        if (sscanf(line1, "%d %d %d: %[^\n]", &year1, &month1, &day1, notes1) == 4) {
            printf("%04d-%02d-%02d  %s\n", year1, month1, day1, notes1);
            eventFound = 1;  
        }
    }

    if (!eventFound) {  
        printf("No event to delete.\n\n");
        return;
    }


    char notes[200], line[200];
    int year, month, day;
    int dyear, dmonth, dday;

    printf("\nEnter the event to delete (yy/mm/dd): ");
    scanf("%d %d %d", &dyear, &dmonth, &dday);

    int deleted = 0;

    while (fgets(line, sizeof(line), src) != NULL) {
        if (sscanf(line, "%d %d %d %[^\n]", &year, &month, &day, &notes) == 4) {
            if (year == dyear && month == dmonth && day == dday) {
                deleted = 1;
                continue;
            }
        }
        fputs(line, temp);
    }

    fclose(src);
    fclose(temp);

    remove("event.txt");
    rename("temp.txt", "event.txt");

    if (deleted) {
        printf("\nEvent deleted successfully!\n");
    } else {
        printf("\nEvent not found.\n");
    }

    printf("----------------------------------------\n");
}


void todo() {
	clrscr();
    int choice;

    printf("------------------------------\n");
    printf("          To-Do List          \n");
    printf("------------------------------\n");

    while (1) {
        printf("\n1. Add To-Do\n");
        printf("2. View To-Do List\n");
        printf("3. Mark Task as Completed\n");
        printf("4. View Completed Tasks\n");
        printf("5. Exit to Main Menu\n");
        printf("---------------------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch (choice) {
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
            return;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
}

void addtodo() {
    FILE* ptr;
    ptr = fopen("todo.txt", "a");
    char task[200];

    printf("\nEnter task to do: ");
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

    fprintf(ptr, "%s\n", task);
    fclose(ptr);
    printf("\nTask added successfully!\n");
    printf("--------------------------------------\n");
}

void viewtodo() {
    FILE *fp = fopen("todo.txt", "r");
    if (!fp) {
        printf("\nNo tasks found.\n");
        return;
    }

    char line[200];
    int count = 1;
    printf("\n--- To-Do List ---\n");

    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        printf("%d. %s\n", count++, line);
    }

    if (count == 1) {
        printf("No tasks found.\n");
    }

    printf("--------------------------\n");
    fclose(fp);
}

void marktodo() {
    FILE* src = fopen("todo.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    FILE* completed = fopen("complete.txt", "a");

    if (!src || !temp || !completed) {
        printf("Error opening files!\n\n");
        return;
    }

    char task[200][200];
    int count = 0;

    while (fgets(task[count], sizeof(task[count]), src)) {
        size_t len = strlen(task[count]);
        if (len > 0 && task[count][len - 1] == '\n') {
            task[count][len - 1] = '\0';
        }
        count++;
    }

    if (count == 0) {
        printf("No tasks found!\n\n");
        fclose(src);
        fclose(temp);
        fclose(completed);
        return;
    }

    int i;

    printf("-- To-Do List --\n");
    for (i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, task[i]);
    }

    int choice;
    printf("Enter task number that is completed: ");
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > count) {
        printf("Invalid choice.\n");
        fclose(src);
        fclose(temp);
        fclose(completed);
        return;
    }

    for (i = 0; i < count; i++) {
        if (i == choice - 1) {
            fprintf(completed, "%s\n", task[i]);
        } else {
            fprintf(temp, "%s\n", task[i]);
        }
    }

    fclose(src);
    fclose(temp);
    fclose(completed);

    remove("todo.txt");
    rename("temp.txt", "todo.txt");

    printf("Task marked as completed.\n");
     printf("--------------------------\n");
}

void view_completedtodo() {
	int i;
    FILE* src = fopen("complete.txt", "r");

    if (!src) {
        printf("Error opening files!\n\n");
        return;
    }

    char task[200][200];
    int count = 0;

    while (fgets(task[count], sizeof(task[count]), src)) {
        size_t len = strlen(task[count]);
        if (len > 0 && task[count][len - 1] == '\n') {
            task[count][len - 1] = '\0';
        }
        count++;
    }

    if (count == 0) {
        printf("\nNo completed tasks.\n\n");
    } else {
        printf("\n--- Completed To-Do List ---\n\n");
        for ( i = 0; i < count; i++) {
            printf("%d. %s\n", i + 1, task[i]);
        }
    }

    fclose(src);
     printf("--------------------------\n");
}
