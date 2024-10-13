#include<stdio.h>
#include<stdlib.h> /* เพื่อ exit(1) */
#include<string.h>
/* Gregorian calender system ค.ศ */
/* คำนวนวันที่ของปีที่กำหนด */

#define max_event 50

void controlpanel();
void listmenu();
int inputyear();
int determineday(int year);
int leapyear(int year);
int totalday(int year);
void showcalender(int year, int daycode);
void addevent(int event[][3], char eventDis[][50],int *eventcount);
void showevent(int event[][3], char eventDis[][50], int eventcount);
void deleteevent(int event[][3], char eventDis[][50], int *eventcount);


int daysinmonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; /* กำหนดวันที่สุดท้ายของเดือน */

char* months[] =
{
    " ",
    "\n---- January ----",
    "\n---- February ----",
    "\n---- March ----",
    "\n---- April ----",
    "\n---- May ----",
    "\n---- June ----",
    "\n---- July ----",
    "\n---- August ----",
    "\n---- September ----",
    "\n---- October ----",
    "\n---- November ----",
    "\n---- December ----"
}; /* กำหนดเดือน */

void controlpanel(int event[][3], char eventDis[][50], int *eventcount) 
{
    int choice;

    do 
    {
        listmenu();
        printf("(use the number to indicates)\nSelect your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:{
            int year = inputyear();
            int daycode = determineday(year);
            leapyear(year); 
            showcalender(year, daycode); 
            break;
        }
        case 2: addevent(event, eventDis, eventcount); break;
        case 3: showevent(event, eventDis, *eventcount); break;
        case 4: deleteevent(event, eventDis, eventcount); break;
        case 0: printf("Exit\n"); break;
        default: printf("Invalid try again\n");
        }
    }while (choice != 0);
}

void listmenu() 
{
    printf("---- SelectChoice ----\n");
    printf("1. Show Calender\n");
    printf("2. Add Event\n");
    printf("3. Search Event\n");
    printf("4. Delete Event\n");
    printf("0. Exit\n");
    printf("----------------------\n");
}

int inputyear()
{
    /* ใส่ปีที่ต้องการ */
    int year;
    printf("Please enter a year : ");
    scanf("%d", &year);
    if (year < 0) {
        printf("invalid number"); /* ใส่เลขติดลบจะบังคับจบทันที */
        exit(1);
    }
    return year;
}

int determineday(int year)
{
    /* หาวันที่เริ่มในเดือน
    เช่นวันที่ 1 คือ วันอังคาร */
    int daycode;
    int d1, d2, d3;

    d1 = (year - 1) / 4.0;
    d2 = (year - 1) / 100.0;
    d3 = (year - 1) / 400.0;
    daycode = (year + d1 - d2 + d3) % 7;
    return daycode;
}

int leapyear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) /* กำหนดวันสุดท้ายของเดือน กุมภา */
    {
        daysinmonth[2] = 29;
        return 1;
    }
    else
    {
        daysinmonth[2] = 28;
        return 0;
    }
}

int totalday (int year){
    int total_days = 0;
    leapyear(year);
    for (int month = 1; month <= 12; month++) {
        total_days += daysinmonth[month];
    }
    return total_days;
}

void showcalender(int year, int daycode)
{
    /* print ข้อมูลทั้งหมด
    พร้อมเรียบเรียงแต่ละบรรทัด */
    int month, day, total_days;
    printf("\n---- Calender for %d ----\n", year);
    for (month = 1; month <= 12; month++)
    {
        printf("%s", months[month]);
        printf("\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        for (day = 0; day < daycode; day++) /* เพิ่มช่องว่างของอาทิตแรกของเดือน */
        {
            printf("     ");
        }

        for (day = 1; day <= daysinmonth[month]; day++) /* print วันในเดือนและช่องว่างระหว่างวัน */
        {
            printf("%2d   ", day);

            if ((day + daycode) % 7 == 0)
                printf("\n");
        }
        daycode = (daycode + daysinmonth[month]) % 7;
        printf("\n");
    }
     total_days = totalday(year);
    printf("\n---- Total days in this year is %d ----\n", total_days);
}

void addevent(int event[][3], char eventDis[][50],int *eventcount) {
    if (*eventcount >= max_event) {
        printf("Add Failled Limit Reached\n");
        return;
    }

    int day, month, year;
    leapyear(year);

    while(1)
    {
        printf("Enter Event Month : ");
        scanf("%d", &month);
        if(month < 1 || month > 12){
            printf("Invalid Month try again\n");
            continue;
        }  

        printf("Enter Event Day : ");
        scanf("%d", &day);
        if(day < 1 || day > daysinmonth[month]){
            printf("Invalid Day try again\n");
            continue;
        }

        printf("Enter Event Year : ");
        scanf("%d", &year);
        if(year < 0){
            printf("I don't think there is Calender in negative-century, so try again\n");
            continue;
        }
        printf("Discription of the event : ");
        scanf(" %[^\n]%*c", eventDis[*eventcount]);

    event[*eventcount][0] = day;
    event[*eventcount][1] = month;
    event[*eventcount][2] = year;

    (*eventcount)++;
    printf("Event Added\n");
    break;
    }
}

void showevent(int event[][3], char eventDis[][50], int eventcount) {
    if (eventcount == 0) {
        printf("No Event Found");
        return;
    }
    else {
        printf("Event Found\n");
        for (int i = 0; i < eventcount; i++)
        printf("Date: %02d/%02d/%04d - Event: %s\n", 
        event[i][0], event[i][1], event[i][2], eventDis[i]);
    }
}

void deleteevent(int event[][3], char eventDis[][50], int *eventcount){
    if(*eventcount == 0) {
        printf("No Event Found\n");
        return;
    }

    int i;
    printf("List of Event \n");
    for(i = 0; i < *eventcount; i++) {
        printf("%d. Data: %02d/%02d/%04d - Discription: %s\n",
        i + 1, event[i][0], event[i][1], event[i][2], eventDis[i]);
    }


    int choice;
    printf("Enter the event to delete: " );
    scanf("%d",&choice);

    if(choice < 1 || choice > *eventcount){
        printf("Invalid Event\n");
        return;
    }

    choice--;

    for (int i = choice; i < *eventcount - 1; i++) {
        event[i][0] = event[i + 1][0];
        event[i][1] = event[i + 2][1];
        event[i][2] = event[i + 3][2];
        strcpy(eventDis[i], eventDis[i + 1]);
    }
    (*eventcount)--;
    printf("Event Deleted\n");
}

int main() /* กำหนดค่า หรือ value ของแต่ละตัวแปร และจัดระเบียบเป็นลำดับ */
{
    int event[max_event][3];
    int eventcount = 0;
    char eventDis[max_event][50];
    controlpanel(event, eventDis, &eventcount);
    return 0;
}