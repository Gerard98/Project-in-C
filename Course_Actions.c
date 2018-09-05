#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#include "Course_Actions.h"
#include <math.h>

course* add_course(course *firstC){
    bool a=false;
    course *tmp;
    course *t = (course*)malloc(sizeof(course));
    // NAME
    printf("Write name of Course\n");
    fflush(stdin);
    fgets(t->course_name, 50, stdin);
    // PRICE
    printf("Write price\n");
    char tmp_price[10];
    fgets(tmp_price,10,stdin);
    while(only_numbers(tmp_price) == false){
        printf("Error! You need to use only digits\n");
        fgets(tmp_price,10,stdin);
    }
    int sum = strlen(tmp_price) - 2;
    t->price = 0;
    for(int i=0; i <= sum; i++){
        t->price += ((tmp_price[i]-48)*pow(10, sum-i));
    }

    // HOURS
    printf("Write number of hours\n");
    char tmp_hours[10];
    fgets(tmp_hours,10,stdin);
    while(only_numbers(tmp_hours) == false){
        printf("Error! You need to use only digits\n");
        fgets(tmp_hours,10,stdin);
    }
    sum = strlen(tmp_hours) - 2;
    t->hours = 0;
    for(int i=0; i <= sum; i++){
        t->hours += ((tmp_hours[i]-48)*pow(10, sum-i));
    }

    // DESCRIPTION
    printf("Write a description ( max 200 letters )\n");
    while(!a){
        a=true;
        fflush(stdin);
        fgets(t->course_description, 200, stdin);
}
    // ID
    a = false;
    while(!a){
    printf("Write a ID of course!");
    tmp = firstC;
    if(tmp) printf("(");
    while(tmp){
        printf("%d ",tmp->id);
        if(!tmp->next) printf(")");
        tmp = tmp->next;
    }
    printf("\n");
    tmp = firstC;

    char tmp_id[10];
    fgets(tmp_id,10,stdin);
    while(only_numbers(tmp_id) == false){
        printf("Error! You need to use only digits\n");
        fflush(stdin);
        fgets(tmp_id,10,stdin);
    }
    sum = strlen(tmp_id) - 2;
    t->id = 0;
    for(int i=0; i <= sum; i++){
        t->id += ((tmp_id[i]-48)*pow(10, sum-i));
    }

    a = true;
    while(tmp){
        if(t->id == tmp->id){
            printf("Error! The course with this id already exist\n");
            a = false;
        }
    tmp = tmp->next;
    }
    }
    add_course_to_list(&firstC, t->id, t->hours, t->price, t->course_name, t->course_description);
    return firstC;
}

course* delete_course(course *firstC, int ID){
course *tmp;
int a=0;
if(firstC == NULL)return firstC;
if(firstC->id == ID){
    tmp = firstC;
    firstC = firstC->next;
    free(tmp);
    }
while(firstC->next){
    if(firstC->next->id == ID){
        tmp = firstC->next;
        firstC->next = tmp->next;
        free(tmp);
        a=1;
        break;
    }
    firstC = firstC->next;
}
if(a == 0)printf("There is no course with this id\n");
return firstC;
}

void edit_course(course* firstC, int ID){
printf("What do you want to edit?\n");
printf("1) Name\n");
printf("2) Description\n");
printf("3) Price\n");
printf("4) Hours\n");
printf("5) Back\n");
int a,halo=1;
while(firstC){
    if(firstC->id == ID)break;
    firstC = firstC->next;
}
do{
scanf("%d",&a);
while(a>5 || a<0)printf("Error!\n");
switch(a){
case 1:
    printf("Write new Name\n");
    fflush(stdin);
    fgets(firstC->course_name, 50, stdin);
    break;
case 2:
    printf("Write new Description\n");
    fflush(stdin);
    fgets(firstC->course_description, 200, stdin);
    break;
case 3:
    printf("Write new Price\n");
    char tmp_price[10];
    fflush(stdin);
    fgets(tmp_price,10,stdin);
    while(only_numbers(tmp_price) == false){
        printf("Error! You need to use only digits\n");
        fflush(stdin);
        fgets(tmp_price,10,stdin);
    }
    int sum = strlen(tmp_price) - 2;
    firstC->price = 0;
    for(int i=0; i <= sum; i++){
        firstC->price += ((tmp_price[i]-48)*pow(10, sum-i));
    }
    break;
case 4:
    printf("Write new number of hours\n");
    char tmp_hours[10];
    fflush(stdin);
    fgets(tmp_hours,10,stdin);
    while(only_numbers(tmp_hours) == false){
        printf("Error! You need to use only digits\n");
        fflush(stdin);
        fgets(tmp_hours,10,stdin);
    }
    sum = strlen(tmp_hours) - 2;
    firstC->hours = 0;
    for(int i=0; i <= sum; i++){
        firstC->hours += ((tmp_hours[i]-48)*pow(10, sum-i));
    }
    break;
case 5:
    return;
}
printf("What would you edit more\n");
}while(halo);
fflush(stdin);
}

void print_one_course(course *firstC){
printf("Cours ID: %d\n",firstC->id);
printf("%s",firstC->course_name);
printf("Hours: %d\n",firstC->hours);
printf("Price: %d\n",firstC->price);
printf("%s\n",firstC->course_description);
}

void sereach_course(course* firstC){
printf("By what you want to sereach course?\n");
printf("1) Name\n");
printf("2) ID\n");
printf("3) Price\n");
course *tmp;
int local_switch, local_ID, local_price;
bool stop;
char local_name[50];
scanf("%d",&local_switch);
switch(local_switch){
case 1:
    tmp = firstC;
    printf("Write the name of the course you are looking for\n");
    fflush(stdin);
    fgets(local_name,50,stdin);
    stop = false;
    while(tmp){
        if( strcmp(tmp->course_name,local_name) == 0 ){
            print_one_course(tmp);
            stop = true;
            break;
        }
    tmp = tmp->next;
    }
    if(stop == false){
        printf("The searched course does not exist\n");
    }
    break;
case 2:
    tmp = firstC;
    printf("Write an ID of the course you are looking for\n");
    scanf("%d",&local_ID);
    stop = false;
    while(tmp){
        if(tmp->id == local_ID){
            print_one_course(tmp);
            stop = true;
            break;
        }
    tmp = tmp->next;
    }
    if(stop == false){
        printf("The searched course does not exist\n");
    }
    break;
case 3:
    tmp = firstC;
    printf("Write the price of the course you are looking for\n");
    scanf("%d",&local_price);
    stop = false;
    while(tmp){
        if(tmp->price == local_price){
            print_one_course(tmp);
            stop = true;
            break;
        }
    tmp = tmp->next;
    }
    if(stop == false){
        printf("The searched course does not exist\n");
    }
    break;
}
}

void sort_course_by_id(course* firstC){
course* tmp = NULL;
course* tmp2 = NULL;
course* tmp3 = (course*)malloc(sizeof(course));
for(tmp = firstC; tmp!=NULL; tmp = tmp->next){
    for(tmp2 = tmp; tmp2!=NULL; tmp2 = tmp2->next){
        if(tmp->id > tmp2->id){
            tmp3->id = tmp->id;
            tmp->id = tmp2->id;
            tmp2->id = tmp3->id;

            strcpy(tmp3->course_description, tmp->course_description);
            strcpy(tmp->course_description, tmp2->course_description);
            strcpy(tmp2->course_description, tmp3->course_description);

            strcpy(tmp3->course_name, tmp->course_name);
            strcpy(tmp->course_name, tmp2->course_name);
            strcpy(tmp2->course_name, tmp3->course_name);

            tmp3->hours = tmp->hours;
            tmp->hours = tmp2->hours;
            tmp2->hours = tmp3->hours;

            tmp3->price = tmp->price;
            tmp->price = tmp2->price;
            tmp2->price = tmp3->price;
        }
    }
}
}

void sort_course_by_hours(course *firstC){
course* tmp = NULL;
course* tmp2 = NULL;
course* tmp3 = (course*)malloc(sizeof(course));
for(tmp = firstC; tmp!=NULL; tmp = tmp->next)
    for(tmp2 = tmp; tmp2!=NULL; tmp2 = tmp2->next){
        if(tmp->hours > tmp2->hours){

            tmp3->id = tmp->id;
            tmp->id = tmp2->id;
            tmp2->id = tmp3->id;

            strcpy(tmp3->course_description, tmp->course_description);
            strcpy(tmp->course_description, tmp2->course_description);
            strcpy(tmp2->course_description, tmp3->course_description);

            strcpy(tmp3->course_name, tmp->course_name);
            strcpy(tmp->course_name, tmp2->course_name);
            strcpy(tmp2->course_name, tmp3->course_name);

            tmp3->hours = tmp->hours;
            tmp->hours = tmp2->hours;
            tmp2->hours = tmp3->hours;

            tmp3->price = tmp->price;
            tmp->price = tmp2->price;
            tmp2->price = tmp3->price;
        }
    }
}

void sort_course_by_price(course *firstC){
course* tmp = NULL;
course* tmp2 = NULL;
course* tmp3 = (course*)malloc(sizeof(course));
for(tmp = firstC; tmp!=NULL; tmp = tmp->next)
    for(tmp2 = tmp; tmp2!=NULL; tmp2 = tmp2->next){
        if(tmp->price > tmp2->price){

            tmp3->id = tmp->id;
            tmp->id = tmp2->id;
            tmp2->id = tmp3->id;

            strcpy(tmp3->course_description, tmp->course_description);
            strcpy(tmp->course_description, tmp2->course_description);
            strcpy(tmp2->course_description, tmp3->course_description);

            strcpy(tmp3->course_name, tmp->course_name);
            strcpy(tmp->course_name, tmp2->course_name);
            strcpy(tmp2->course_name, tmp3->course_name);

            tmp3->hours = tmp->hours;
            tmp->hours = tmp2->hours;
            tmp2->hours = tmp3->hours;

            tmp3->price = tmp->price;
            tmp->price = tmp2->price;
            tmp2->price = tmp3->price;
        }
    }
}

void sort_courses(course* firstC){
bool stop = true;
while(stop){
printf("By what you want to sort courses?\n");
printf("1) ID\n");
printf("2) Hours\n");
printf("3) Price\n");
printf("4) If you dont wanna sort\n");
int local_menu;
scanf("%d",&local_menu);
while(local_menu < 1 || local_menu > 4){
    printf("Error! You need to write a number between 1-4\n");
    scanf("%d",&local_menu);
}
stop = false;
    switch(local_menu){
        case 1:
            sort_course_by_id(firstC);
            fflush(stdin);
            break;
        case 2:
            sort_course_by_hours(firstC);
            fflush(stdin);
            break;
        case 3:
            sort_course_by_price(firstC);
            break;
        case 4:
            return;
    }
}
}

